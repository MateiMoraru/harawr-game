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

        void draw();
        void update();

        void move(float x, float y);

        float get_x() { return position.x; }
        float get_y() { return position.y; }
        float get_x_offset() { return offset.x; }
        float get_y_offset() { return offset.y; }

    private:
        sf::RenderWindow& window;
        Spritesheet& spritesheet;
        Tile player;
        int size = 64;
        sf::Vector2f position;
        float speed = 5.f;
};

#endif