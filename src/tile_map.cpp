#include "tile_map.h"
#include <random>
#include <algorithm>

float random_float(float min, float max)
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rng);
}

TileMap::TileMap(sf::RenderWindow &window, Spritesheet &spritesheet, SoundSystem &soundsystem) : window(window), spritesheet(spritesheet)
{

    for(int i = 0; i < 2000; i += 150 + random_float(-100, 0))
    {
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
                x - fmod(x, tile_size),
                y - fmod(y, tile_size)
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
}

void TileMap::draw(Player &player, sf::RenderStates &states)
{

    float brightness_min = random_float(0.f, 0.01f);
    sf::FloatRect view(player.get_x_offset(), player.get_y_offset(), window.getSize().x, window.getSize().y);

    for(Tile &tile : tile_map)
    {
        if(!tile.get_global_bounds().intersects(view))
            continue;
        float max_distance = (7.f + random_float(0.f, .1f)) * tile_size;

        float distance = std::hypot(
            tile.get_x() - player.get_x(),
            tile.get_y() - player.get_y()
        );

        float dx = tile.get_x() - player.get_x();
        float dy = tile.get_y() - player.get_y();
        float dist2 = dx*dx + dy*dy;
        float max_dist = max_distance*max_distance;
        float brightness = clamp(1.f - dist2 / max_dist, brightness_min, .9f);

        sf::Uint8 light = static_cast<sf::Uint8>(255 * brightness);
        tile.set_sprite_color(sf::Color(255, 217, 166, light));
        tile.draw(window, states);

        if(dist2 < tile_size * 2)
        {
            
        }
    }

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

        tile_map.push_back(tile);

        if(id == JUMPSCARE_BLOCK)
            jumpscares.push_back(Jumpscare(soundsystem, window, 0, sf::Vector2f(x, y), tile_map.size() - 1));
        if(find(collidable.begin(), collidable.end(), id) != collidable.end())
        {
            collidable_tiles.push_back(tile);
        }
    }
}

void TileMap::scroll(int delta)
{
    selected_tile_id += delta;
}

