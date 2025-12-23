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
          PLAYER = 10,
          JUMPSCARE_1 = 20;

class Spritesheet
{
    public:
        Spritesheet();

        sf::Sprite get_sprite(int id);

    private:
        sf::Texture spritesheet;
        vector<sf::Sprite> sprites;

        const int SIZE = 256;
        const int TILE_SIZE = 16;
};

#endif