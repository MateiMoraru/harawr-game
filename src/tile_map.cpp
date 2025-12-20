#include "tile_map.h"

TileMap::TileMap(sf::RenderWindow &window, Spritesheet &spritesheet) : window(window), spritesheet(spritesheet)
{
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
                cout << "mouse clicked at " << mouse_pos.x << " " << mouse_pos.y << endl; 
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

void TileMap::scroll(int delta)
{
    selected_tile_id += delta;
}