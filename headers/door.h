#ifndef DOOR_H
#define DOOR_H

#include <SFML/Graphics.hpp>

#include "spritesheet.h"
#include "sound_system.h"
#include "tile.h"

class Door
{
    public:
        Door(sf::RenderWindow &window, Spritesheet &spritesheet, SoundSystem &soundsystem, sf::Vector2f position, sf::Vector2f size, int id, int index);

        void draw(sf::RenderStates &states);
        void unlock();

        sf::Sprite get_sprite() { return door.get_sprite(); }
        int get_key() const { return key; }
        int get_index() const { return index; }
        int get_id() const { return id; }
        float get_x() const { return position.x; }
        float get_y() const { return position.y; }
        bool is_open() const { return opened; }

        void set_sprite_color(sf::Color color) { door.set_sprite_color(color); }

    private:
        sf::RenderWindow &window;
        Spritesheet &spritesheet;
        SoundSystem &soundsystem;

        Tile door;

        sf::Vector2f position;
        sf::Vector2f size;
        int id;
        int index;
        int key;
        bool opened = false;
};

#endif
