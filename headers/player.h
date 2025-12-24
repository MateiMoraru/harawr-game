#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "tile.h"
#include "spritesheet.h"

using namespace std;

class Player
{
    public:
        Player(sf::RenderWindow &window, Spritesheet &spritesheet);
        
        sf::Vector2f offset;

        void draw(sf::RenderStates states);
        void update();

        void move(float x, float y);

        float get_x() const { return position.x; }
        float get_y() const { return position.y; }
        float get_x_offset() const { return offset.x; }
        float get_y_offset() const { return offset.y; }
        float get_speed() const { return speed; }
        sf::Vector2f get_moved() const { return moved; }
        sf::Sprite get_sprite() const { return player.get_sprite(); }

        void set_size(float x, float y);

    private:
        sf::RenderWindow& window;
        Spritesheet& spritesheet;
        
        Tile player;
        
        int size = 64;
        
        sf::Vector2f moved;
        sf::Vector2f position;
        float speed = 5.f;

};

#endif