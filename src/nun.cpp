#include "nun.h"

Nun::Nun(sf::RenderWindow &window, Spritesheet &spritesheet, SoundSystem &soundsystem, sf::Vector2f position, sf::Vector2f size)
      : window(window),
        spritesheet(spritesheet),
        soundsystem(soundsystem),
        position(position),
        size(size),
        nun(spritesheet.get_sprite(NUN_UP), NUN_UP, position, size)
{

}

void Nun::draw(sf::RenderStates &states, sf::Color color)
{
    nun.set_sprite_color(color);
    nun.draw(window, states);
}

void Nun::update(Player &player)
{
    float dx = player.get_x() - position.x + size.x / 2;
    float dy = player.get_y() - position.y + size.y / 2;

    distance = std::sqrt(dx * dx + dy * dy);

    if (distance > 0.001f)
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