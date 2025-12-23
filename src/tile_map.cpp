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

    for(int i = 0; i < 2000; i += 150 + random_float(-100, 0))
    {
        line_overlay.push_back(pair<float, float>(i, random_float(0.5, 15)));
    }
    load();
    
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

}

void TileMap::draw(Player &player, sf::RenderStates &states)
{
    sf::FloatRect view(player.get_x_offset(), player.get_y_offset(), window.getSize().x, window.getSize().y);

    float brightness_min = random_float(0.f, 0.07f);

    for(Tile &tile : tile_map)
    {
        if(!tile.get_global_bounds().intersects(view))
            continue;
        float maxDistance = 5.f * tile_size;

        float distance = std::hypot(
            tile.get_x() - player.get_x(),
            tile.get_y() - player.get_y()
        );

        float dx = tile.get_x() - player.get_x();
        float dy = tile.get_y() - player.get_y();
        float dist2 = dx*dx + dy*dy;
        float max_dist = maxDistance*maxDistance;
        float brightness = clamp(1.f - dist2 / max_dist, brightness_min, 1.f);

        sf::Uint8 light = static_cast<sf::Uint8>(255 * brightness);
        tile.set_sprite_color(sf::Color(light, light, light));
        tile.draw(window, states);
    }
}

void TileMap::draw_overlay()
{

    //thick_line.setFillColor(sf::Color(0, 0, 0, 100));
    //thick_line.setPosition(0, 0);
    //thick_line.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    //window.draw(thick_line);
    
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
    ofstream out("assets/map.txt");

    for(Tile tile : tile_map)
    {
        out << tile.get_id() << ' ' << tile.get_x() << ' ' << tile.get_y() << '\n';
    }
}

void TileMap::load()
{
    ifstream in("assets/map.txt");
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
    }
}

void TileMap::scroll(int delta)
{
    selected_tile_id += delta;
}

