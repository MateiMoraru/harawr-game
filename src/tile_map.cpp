#include "tile_map.h"

inline sf::Color compute_light(float obj_x, float obj_y, float obj_size,
                               float player_x, float player_y, float player_size,
                               float max_distance, float brightness_min = 0.01f, float brightness_max = 0.9f)
{
    // Distance between centers
    float dx = (obj_x + obj_size / 2.f) - (player_x + player_size / 2.f) + 64;
    float dy = (obj_y + obj_size / 2.f) - (player_y + player_size / 2.f);
    float dist2 = dx * dx + dy * dy;
    float max_dist2 = max_distance * max_distance;
    float brightness = std::clamp(1.f - dist2 / max_dist2, brightness_min, brightness_max);
    sf::Uint8 alpha = static_cast<sf::Uint8>(255 * brightness);
    return sf::Color(255, 217, 166, alpha); // same as before
}

float random_float(float min, float max)
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rng);
}

TileMap::TileMap(sf::RenderWindow &window, Spritesheet &spritesheet, SoundSystem &soundsystem) : window(window), spritesheet(spritesheet), soundsystem(soundsystem)
{

    for(int i = 0; i < 2000; i += 150 + random_float(-100, 0))
    {
        if(i < window.getSize().y / 2 - 100 || i > window.getSize().y / 2 + 100)
            line_overlay.push_back(pair<float, float>(i, random_float(0.5, 15)));
    }
    load(soundsystem);
    
}

void TileMap::update(Player &player)
{
    if(is_editing)
    {
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            float x = mouse_pos.x + player.offset.x;
            float y = mouse_pos.y + player.offset.y;
            
            sf::Vector2f mouse_pos_relative(
                x - (int)(x) % tile_size,
                y - (int)(y) % tile_size - tile_size
            );
            
            Tile temp_tile = Tile(spritesheet.get_sprite(selected_tile_id), selected_tile_id, mouse_pos_relative, sf::Vector2f(tile_size, tile_size));

            bool collides = false;

            for(int i = tile_map.size() - 10; i < tile_map.size(); i++)
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
                player.move(player.get_speed(), 0);
            }
            if(tile.get_x() > player.get_x() && player.get_moved().x > 0)
            {
                player.move(-player.get_speed(), 0);
            }
            if(tile.get_y() < player.get_y() && player.get_moved().y < 0)
            {
                player.move(0, player.get_speed());
            }
            if(tile.get_y() > player.get_y() && player.get_moved().y > 0)
            {
                player.move(0, -player.get_speed());
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
}

void TileMap::draw(Player &player, sf::RenderStates &states)
{
    float max_distance = (7.f + random_float(0.f, 0.1f)) * tile_size;
    float brightness_min = random_float(0.f, 0.01f);
    sf::FloatRect view(player.get_x_offset(), player.get_y_offset(), window.getSize().x, window.getSize().y);

    for(Tile &tile : tile_map)
    {
        if(!tile.get_global_bounds().intersects(view))
            continue;
        float max_distance = (7.f + random_float(0.f, .1f)) * tile_size;

        tile.set_sprite_color(compute_light(
            tile.get_x(), tile.get_y(), tile_size,     // tile position & size
            player.get_x(), player.get_y(), player.get_size(), // player position & size
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

            // if(player.get_sprite().getGlobalBounds().intersects(door.get_sprite().getGlobalBounds()))
            if(dist2 < 2 * tile_size) 
            {
                if(player.has_in_inventory(door.get_key())) 
                {
                    door.unlock();
                    // collidable_tiles[door.get_index()] = collidable_tiles.back();
                    // collidable_tiles.pop_back();
                }
            }
         
            if(player.get_sprite().getGlobalBounds().intersects(door.get_sprite().getGlobalBounds())) 
            {
                if(door.get_x() < player.get_x() && player.get_moved().x < 0) 
                {
                    player.move(player.get_speed(), 0);
                }
                if(door.get_x() > player.get_x() && player.get_moved().x > 0) 
                {
                    player.move(-player.get_speed(), 0);
                }
                if(door.get_y() < player.get_y() && player.get_moved().y < 0) 
                {
                    player.move(0, player.get_speed());
                }
                if(door.get_y() > player.get_y() && player.get_moved().y > 0) 
                {
                    player.move(0, -player.get_speed());
                }
            }
        }
    }


    for(Tile &key : keys)
    {
        if(!key.get_global_bounds().intersects(view))
            continue;

        key.set_sprite_color(compute_light(
            key.get_x(), key.get_y(), tile_size,
            player.get_x(), player.get_y(), player.get_size(),
            max_distance
        ));
        key.draw(window, states);
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
        out << tile.get_id() << ' ' << tile.get_x() << ' ' << tile.get_y() << '\n';
    }
    for(Door &door : doors)
    {
        out << door.get_id() << ' ' << door.get_x() << ' ' << door.get_y() << '\n';
    }
    for(Tile &key : keys)
    {
        out << key.get_id() << ' ' << key.get_x() << ' ' << key.get_y() << endl;
    }
}

void TileMap::load(SoundSystem &soundsystem)
{
    ifstream in("assets/data/map.txt");
    if(!in.is_open())
    {
        cout << "Nothing to load :(" << endl;
        return;
    }
    
    float x, y, id;
    while(in >> id)
    {
        in >> x;
        in >> y;

        Tile tile(spritesheet.get_sprite(id), id, sf::Vector2f(x, y), sf::Vector2f(tile_size, tile_size));

        if(!(id == KEY_YELLOW || id == KEY_BLUE || id == KEY_RED || id == KEY_GREEN) && !(id >= DOOR_YELLOW && id <= DOOR_GREEN))
            tile_map.push_back(tile);

        if(id == JUMPSCARE_BLOCK)
            jumpscares.push_back(Jumpscare(soundsystem, window, 0, sf::Vector2f(x, y), tile_map.size() - 1));
        if(find(collidable.begin(), collidable.end(), id) != collidable.end())
        {
            collidable_tiles.push_back(tile);
        }
        if(id >= DOOR_YELLOW && id <= DOOR_GREEN)
        {
            Door door = Door(window, spritesheet, soundsystem, sf::Vector2f(x, y), sf::Vector2f(tile_size, tile_size), id, collidable_tiles.size() - 1);
            doors.push_back(door);
        }
        if(id == KEY_YELLOW || id == KEY_BLUE || id == KEY_RED || id == KEY_GREEN)
        {
            keys.push_back(tile);
        }
    }
}

void TileMap::scroll(int delta)
{
    selected_tile_id += delta;
}

