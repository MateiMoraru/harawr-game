#include "tile_map.h"
#include <random>

float random_float(float min, float max)
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rng);
}

TileMap::TileMap(sf::RenderWindow &window, Spritesheet &spritesheet) : window(window), spritesheet(spritesheet)
{

    for(int i = 0; i < 2000; i += 200 + random_float(-100, 0))
    {
        line_overlay.push_back(pair<float, float>(i, random_float(0.5, 5)));
    }
    
}

void TileMap::update()
{
    if(is_editing)
    {
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2f mouse_pos_relative(mouse_pos.x - mouse_pos.x % tile_size, mouse_pos.y - mouse_pos.y % tile_size);
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
}

void TileMap::draw()
{
    for(Tile tile : tile_map)
    {
        tile.draw(window);
    }
}

void TileMap::draw_overlay()
{
    sf::RectangleShape thick_line;

    thick_line.setFillColor(sf::Color(0, 0, 0, 100));
    thick_line.setPosition(0, 0);
    thick_line.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    window.draw(thick_line);
    
    thick_line.setFillColor(sf::Color::Black);
    thick_line.setSize(sf::Vector2f(window.getSize().x, 0.5f));

    for (int i = 0; i < line_overlay.size(); i ++)
    {
        thick_line.setSize(sf::Vector2f(window.getSize().x, line_overlay[i].second));
        thick_line.setPosition(sf::Vector2f(0.0f, line_overlay[i].first));
        window.draw(thick_line);
    }


}

void TileMap::scroll(int delta)
{
    selected_tile_id += delta;
}

