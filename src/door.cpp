#include "door.h"

Door::Door(sf::RenderWindow &window, Spritesheet &spritesheet, SoundSystem &soundsystem,
           sf::Vector2f position, sf::Vector2f size, int id, int index)
    : window(window), 
      spritesheet(spritesheet), 
      soundsystem(soundsystem),
      position(position), 
      size(size), 
      id(id),
      door(spritesheet.get_sprite(id), id, position, size)
{
    if(id == DOOR_YELLOW)
        key = KEY_YELLOW;
    if(id == DOOR_BLUE)
        key = KEY_BLUE;
    if(id == DOOR_RED)
        key = KEY_RED;
    if(id == DOOR_GREEN)
        key = KEY_GREEN;
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