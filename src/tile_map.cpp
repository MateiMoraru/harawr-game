#include "tile_map.h"

inline sf::Color compute_light(float obj_x, float obj_y, float obj_size, float player_x, float player_y, float player_size, float max_distance = 7.0f * 64, float brightness_min = 0.04f, float brightness_max = 0.5f)
{
    float dx = (obj_x + obj_size / 2.f) - (player_x + player_size / 2.f) + 64;
    float dy = (obj_y + obj_size / 2.f) - (player_y + player_size / 2.f);
    float dist2 = dx * dx + dy * dy;
    float max_dist2 = max_distance * max_distance;
    float brightness = std::clamp(1.f - dist2 / max_dist2, brightness_min, brightness_max);
    sf::Uint8 alpha = static_cast<sf::Uint8>(255 * brightness);
    return sf::Color(255, 217, 166, alpha);
}

float random_float(float min, float max)
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rng);
}


TileMap::TileMap(sf::RenderWindow &window, Spritesheet &spritesheet, SoundSystem &soundsystem) : window(window), spritesheet(spritesheet), soundsystem(soundsystem), tasks(window, font)
{

    for(int i = 0; i < 2000; i += 150 + random_float(-100, 0))
    {
        if(i < window.getSize().y / 2 - 100 || i > window.getSize().y / 2 + 100)
            line_overlay.push_back(pair<float, float>(i, random_float(0.5, 15)));
    }
    load(soundsystem);

    font.loadFromFile("assets/font/pixelated.ttf");
    tasks.set_font(font);
    
}

void TileMap::update(Player &player, float delta_time)
{
    elapsed_time_door_knock += delta_time;
    if(elapsed_time_door_knock > 15.0f && random_float(0, 1.f) >= 0.99f)
    {
        soundsystem.play_sound(DOOR_KNOCK, 0.5, 2);
        elapsed_time_door_knock = 0;
    }

    if(is_editing)
    {
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            float x = mouse_pos.x + player.offset.x;
            float y = mouse_pos.y + player.offset.y;
            
            int tilex = (int)std::floor(x / tile_size);
            int tiley = (int)std::floor(y / tile_size);

            sf::Vector2f mouse_pos_relative(
                tilex * tile_size,
                tiley * tile_size
            );

            
            Tile temp_tile = Tile(spritesheet.get_sprite(selected_tile_id), selected_tile_id, mouse_pos_relative, sf::Vector2f(tile_size, tile_size));

            bool collides = false;

            for(int i = tile_map.size() - 2; i < tile_map.size(); i++)
            {
                if(tile_map[i].collides(temp_tile))
                {
                    collides = true;
                }
            }

            if(!collides)
            {
                tile_map.push_back(temp_tile);
            }
        }
        else if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            float x = mouse_pos.x + player.offset.x;
            float y = mouse_pos.y + player.offset.y;
            
            for(int i = 0; i < tile_map.size(); i++)
            {
                if (x > tile_map[i].get_x() &&
                    x < tile_map[i].get_x() + tile_size &&
                    y > tile_map[i].get_y() &&
                    y < tile_map[i].get_y() + tile_size)
                {
                    std::swap(tile_map[i], tile_map.back());
                    tile_map.pop_back();
                    break;
                }
                
            }
        }
    }

    sf::FloatRect view(player.get_x_offset(), player.get_y_offset(), window.getSize().x, window.getSize().y);

    for(Tile &tile : collidable_tiles)
    {
        if(!tile.get_global_bounds().intersects(view))
            continue;
        if(player.get_sprite().getGlobalBounds().intersects(tile.get_global_bounds()))
        {
            if(tile.get_x() < player.get_x() && player.get_moved().x < 0)
            {
                player.move(player.get_speed() * delta_time, 0);
            }
            if(tile.get_x() > player.get_x() && player.get_moved().x > 0)
            {
                player.move(-player.get_speed() * delta_time, 0);
            }
            if(tile.get_y() < player.get_y() && player.get_moved().y < 0)
            {
                player.move(0, player.get_speed() * delta_time);
            }
            if(tile.get_y() > player.get_y() && player.get_moved().y > 0)
            {
                player.move(0, -player.get_speed() * delta_time);
            }
        }
    }

    for(Tile &key : keys)
    {
        if(!key.get_global_bounds().intersects(view))
            continue;
        if(player.get_sprite().getGlobalBounds().intersects(key.get_global_bounds()))
        {
            player.add_key(key.get_id());
            auto it = std::find_if(
                keys.begin(),
                keys.end(),
                [&](const Tile& t) {
                    return t.get_id() == key.get_id();
                }
            );

            size_t index = it - keys.begin();
            keys[index] = keys.back();
            keys.pop_back();

            soundsystem.play_sound(KEY_PICKUP);
        }
    }

    for (Nun &nun : nuns)
    {
        nun.update(player);

        if (!nun.is_active() && nun.get_distance() < tile_size * 5.f)
        {
            nun.set_active(true);
            soundsystem.play_sound(JUMPSCARE, 0.7, 1.5);
            soundsystem.play_loop_sound(HAUNT);
            haunt_sound_index = soundsystem.get_looped().size() - 1;
        }

        if (nun.is_active())
        {
            sf::Vector2f delta = nun.get_direction() * nun.get_speed() * delta_time;

            nun.move(delta.x, 0);
            if (nun.collides(collidable_tiles))
                nun.move(-delta.x, 0);

            nun.move(0, delta.y);
            if (nun.collides(collidable_tiles))
                nun.move(0, -delta.y);
        }
    }
}

void TileMap::draw(Player &player, sf::RenderStates &states, float delta_time)
{
    float max_distance = (7.f + random_float(0.f, 0.2f)) * tile_size;
    float brightness_min = random_float(0.f, 0.0f);
    sf::FloatRect view(player.get_x_offset(), player.get_y_offset(), window.getSize().x, window.getSize().y);

    for(Tile &tile : tile_map)
    {
        if(!tile.get_global_bounds().intersects(view))
            continue;
        float max_distance = (7.f + random_float(0.f, .1f)) * tile_size;

        tile.set_sprite_color(compute_light(
            tile.get_x(), tile.get_y(), tile_size,
            player.get_x(), player.get_y(), player.get_size(),
            max_distance
        ));
        tile.draw(window, states);
    }

    for(Door &door : doors) 
    {
        if(!door.is_open()) 
        {
            door.set_sprite_color(compute_light(player.get_x(), player.get_y(), tile_size, door.get_x(), door.get_y(), tile_size, max_distance));
            door.draw(states);

            float dx = door.get_x() - player.get_x() + player.get_size() / 2;
            float dy = door.get_y() - player.get_y() + player.get_size() / 2;
            float dist2 = sqrt(dx*dx + dy*dy);

            if(dist2 < 2 * tile_size) 
            {
                if(player.has_in_inventory(door.get_key())) 
                {
                    door.unlock();
                }
            }
         
            if(player.get_sprite().getGlobalBounds().intersects(door.get_sprite().getGlobalBounds())) 
            {
                if(door.get_x() < player.get_x() && player.get_moved().x < 0) 
                {
                    player.move(player.get_speed() * delta_time, 0);
                }
                if(door.get_x() > player.get_x() && player.get_moved().x > 0) 
                {
                    player.move(-player.get_speed() * delta_time, 0);
                }
                if(door.get_y() < player.get_y() && player.get_moved().y < 0) 
                {
                    player.move(0, player.get_speed() * delta_time);
                }
                if(door.get_y() > player.get_y() && player.get_moved().y > 0) 
                {
                    player.move(0, -player.get_speed() * delta_time);
                }
            }
        }
    }

    for(Nun &nun : nuns)
    {
        sf::Color color = compute_light(nun.get_x(), nun.get_y(), tile_size, player.get_x(), player.get_y(), player.get_size(), 6 * tile_size, 0.f);

        nun.draw(states, color);
        nun.draw(states, color);
        nun.draw(states, color);
    }

}

void TileMap::draw_keys(Player &player, sf::RenderStates &states)
{
    for (size_t i = 0; i < keys.size(); )
    {
        Tile &key = keys[i];
        key.set_sprite_color(compute_light(key.get_x(), key.get_y(), tile_size, player.get_x(), player.get_y(), tile_size, 7.f * tile_size));
        key.draw(window, states);

        if (player.get_sprite().getGlobalBounds().intersects(key.get_global_bounds()))
        {
            player.add_key(key.get_id());
            soundsystem.play_sound(KEY_PICKUP);

            key = keys.back();
            keys.pop_back();
        }
        else
        {
            ++i;
        }
    }
}

void TileMap::draw_notes(Player &player)
{
    for(Note &note : notes)
    {
        float dx = (note.get_x() + tile_size / 2.f) - (player.get_x() + player.get_size() / 2.f) + 64;
        float dy = (note.get_y() + tile_size / 2.f) - (player.get_y() + player.get_size() / 2.f);
        float dist = sqrt(dx * dx + dy * dy);

        if(dist <= tile_size * 1.5)
        {
            if(!note.is_displayed())
            {
                soundsystem.play_sound(PAGE_TURN);
                note.display();
            }
            
            note.draw();
        }
    }
}

void TileMap::draw_jumpscares(Player &player)
{
    for(int i = 0; i < jumpscares.size(); i++)
    {
        Jumpscare &jumpscare = jumpscares[i];
        float dx = jumpscare.get_x() - player.get_x();
        float dy = jumpscare.get_y() - player.get_y();
        if(!jumpscare.is_triggered() && !jumpscare.is_expired() && sqrt(dx * dx + dy * dy) < tile_size * 3)
        {
            jumpscare.trigger();
        }
        jumpscare.draw();
        if(jumpscare.is_expired() && !jumpscare.is_deleted())
        {
            jumpscare.delete_();
            tile_map[jumpscare.get_index()] = tile_map.back();
            tile_map.pop_back();
        }
    }
}

void TileMap::draw_tasks()
{
    tasks.draw();
}

void TileMap::draw_overlay()
{
    thick_line.setFillColor(sf::Color::Black);

    for (int i = 0; i < line_overlay.size(); i ++)
    {
        thick_line.setSize(sf::Vector2f(window.getSize().x, line_overlay[i].second));
        thick_line.setPosition(sf::Vector2f(0.0f, line_overlay[i].first));
        window.draw(thick_line);
    }
}

void TileMap::save()
{
    ofstream out("assets/data/map.txt");

    for(Tile tile : tile_map)
    {
        if(tile.get_id() == JUMPSCARE_BLOCK)
            out << tile.get_id() << ' ' << tile.get_x() << ' ' << tile.get_y() << tile.get_id() << endl;
        else
            out << tile.get_id() << ' ' << tile.get_x() << ' ' << tile.get_y() << endl;
    }
    for(Door &door : doors)
        out << door.get_id() << ' ' << door.get_x() << ' ' << door.get_y() << endl;
    for(Tile &key : keys)
        out << key.get_id() << ' ' << key.get_x() << ' ' << key.get_y() << endl;
    for(Jumpscare &j : jumpscares)
        out << JUMPSCARE_BLOCK << ' ' << j.get_x() << ' ' << j.get_y() << ' ' <<  j.get_id() << endl;
    for(Nun &nun: nuns)
        out << NUN_LEFT << ' ' << nun.get_x() << ' ' << nun.get_y() << ' ' << endl;

    cout << "Map saved" << endl;
}
void TileMap::load(SoundSystem &soundsystem)
{

    sf::Clock timer;

    tile_map.clear();
    doors.clear();
    keys.clear();
    collidable_tiles.clear();
    tile_map.reserve(1000);
    doors.reserve(10);
    keys.reserve(3);
    collidable_tiles.reserve(1000);

    ifstream in("assets/data/map.txt");
    if(!in.is_open())
    {
        cout << "Nothing to load :(" << endl;
        return;
    }

    float x, y, id, jumpscare_temp;
    while(in >> id >> x >> y)
    {
        if(!(id == KEY_YELLOW || id == KEY_BLUE || id == KEY_RED || id == KEY_GREEN) && !(id >= DOOR_YELLOW && id <= DOOR_GREEN) && id != NUN_LEFT)
        {
            tile_map.emplace_back(
                spritesheet.get_sprite(id),
                id,
                sf::Vector2f(x, y),
                sf::Vector2f(tile_size, tile_size)
            );
        }

        if(id == NUN_LEFT)
        {
            cout << 0 << endl;
            nuns.push_back(Nun(window, spritesheet, soundsystem, sf::Vector2f(x, y), sf::Vector2f(tile_size, tile_size)));
        }

        if(id == JUMPSCARE_BLOCK)
        {
            in >> jumpscare_temp;
            jumpscares.emplace_back(soundsystem, window, jumpscare_temp, sf::Vector2f(x, y), tile_map.size() - 1);
        }

        if(find(collidable.begin(), collidable.end(), id) != collidable.end())
        {
            collidable_tiles.emplace_back(
                spritesheet.get_sprite(id),
                id,
                sf::Vector2f(x, y),
                sf::Vector2f(tile_size, tile_size)
            );
        }

        if(id >= DOOR_YELLOW && id <= DOOR_GREEN)
        {
            doors.emplace_back(
                window,
                spritesheet,
                soundsystem,
                sf::Vector2f(x, y),
                sf::Vector2f(tile_size, tile_size),
                id,
                collidable_tiles.size() - 1
            );
        }

        if(id == KEY_YELLOW || id == KEY_BLUE || id == KEY_RED || id == KEY_GREEN)
        {
            keys.emplace_back(
                spritesheet.get_sprite(id),
                id,
                sf::Vector2f(x, y),
                sf::Vector2f(tile_size, tile_size)
            );
        }

        if(id == BUTTON)
        {
            notes.emplace_back(window, spritesheet, font, 1, sf::Vector2f{x, y});
        }
    }

    cout << "Map loaded successfully (" << timer.getElapsedTime().asSeconds() << "s)" << endl;
}


void TileMap::scroll(int delta)
{
    selected_tile_id = clamp(selected_tile_id + delta, 0, 64);
}

