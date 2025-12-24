#ifndef DOOR_H
#define DOOR_H

#include <SFML/Graphics.hpp>

#include "spritesheet.h"
#include "sound_system.h"
#include "tile.h"

class Door
{
    public:
        Door(sf::RenderWindow &window, Spritesheet &spritesheet, SoundSystem &soundsystem, sf::Vector2f position, sf::Vector2f size, int id);

        void draw(sf::RenderStates &states);
        void unlock();

        sf::Sprite get_sprite() { return door.get_sprite(); }

    private:
        sf::RenderWindow &window;
        Spritesheet &spritesheet;
        SoundSystem &soundsystem;

        Tile door;

        sf::Vector2f position;
        sf::Vector2f size;
        int id;
        int key;
        bool opened = false;
};

#endif
