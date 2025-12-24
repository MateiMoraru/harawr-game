#include "door.h"

Door::Door(sf::RenderWindow &window, Spritesheet &spritesheet, SoundSystem &soundsystem, sf::Vector2f position, sf::Vector2f size, int id)
    : window(window),
      spritesheet(spritesheet),
      soundsystem(soundsystem),
      position(position),
      size(size),
      id(id)
{
    door = Tile(spritesheet.get_sprite(id), id);
    if(id == DOOR_YELLOW || id == DOOR_BLUE)
    {
        key = id + 10;
    }
    else
    {
        key = id + 18;
    }
}

void Door::draw(sf::RenderStates &states)
{
    if(!opened)
        door.draw(window, states);
}

void Door::unlock()
{
    opened = true;
    soundsystem.play_sound(DOOR_OPEN);
}