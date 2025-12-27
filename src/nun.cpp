#include "nun.h"

Nun::Nun(sf::RenderWindow &window, Spritesheet &spritesheet, SoundSystem &soundsystem, sf::Vector2f position, sf::Vector2f size)
      : window(window),
        spritesheet(spritesheet),
        soundsystem(soundsystem),
        position(position),
        start_position(position),
        size(size),
        nun(spritesheet.get_sprite(NUN_UP), NUN_UP, position, size)
{

}

void Nun::restart()
{
    active = false;
    position = start_position;
    nun.set_position(position.x, position.y);
    positions.clear(); 
    dt = 0.f;
    distance = 1000.f;
}

void Nun::draw(sf::RenderStates &states, sf::Color color)
{
    nun.set_sprite_color(color);
    nun.draw(window, states);
}

void Nun::update(Player &player, float delta_time)
{
    dt += delta_time;
    float dx = player.get_x() - position.x - size.x / 2;
    float dy = player.get_y() - position.y - size.y / 2;

    distance = std::sqrt(dx * dx + dy * dy);

    if((int) (dt * 10) % 5 == 0)
    {
        //position.y -= size.x / 8 * fly_dir;
        //fly_dir *= -1;
    }
    
    if(dt > 1 && active)
    {
        dt = 0;
        positions.push_back(sf::Vector2f(player.get_x(), player.get_y()));
        
        nun.set_position(position.x, position.y);
    }

    if (distance > 10.f * size.x && !positions.empty())
    {
        int idx = max(0, (int)positions.size() - 3);

        position = positions[idx];
        nun.set_position(position.x, position.y);

        positions.erase(positions.begin(), positions.begin() + idx);
    }

    if(distance > 0.001f)
    {
        direction.x = dx / distance;
        direction.y = dy / distance;
    }

    if(abs(direction.x) > abs(direction.y))
    {
        if(direction.x < 0)
            nun.set_sprite(spritesheet.get_sprite(NUN_LEFT), NUN_LEFT);
        else if(direction.x > 0)
            nun.set_sprite(spritesheet.get_sprite(NUN_RIGHT), NUN_RIGHT);
    }
    else
    {
        if(direction.y < 0)
            nun.set_sprite(spritesheet.get_sprite(NUN_UP), NUN_UP);
        else if(direction.y> 0)
            nun.set_sprite(spritesheet.get_sprite(NUN_DOWN), NUN_DOWN);
    }

    //UH OH TILE SIZE SHITTY SCALE
    nun.set_scale(sf::Vector2f(4, 4));
}

void Nun::move(float x, float y)
{
    position.x += x;
    position.y += y;

    nun.set_position(position.x, position.y);
}

bool Nun::collides(vector<Tile> &collidable_tiles)
{
    for(Tile &tile : collidable_tiles)
    {
        if(nun.get_sprite().getGlobalBounds().intersects(tile.get_global_bounds()))
        {
            return true;
        }
    }
    return false;
}