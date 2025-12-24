#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

//TEXTURES
const int NULL_TEX = 0, // Error texture
          FLOOR = 1,
          BRICK = 2,
          JUMPSCARE_BLOCK = 3,
          PLAYER = 9;

extern vector<int> collidable;

class Spritesheet
{
    public:
        Spritesheet();

        void draw(sf::RenderWindow &window);

        sf::Sprite get_sprite(int id);

    private:
        sf::Texture spritesheet;
        vector<sf::Sprite> sprites;

        const int SIZE = 256;
        const int TILE_SIZE = 16;
};

#endif