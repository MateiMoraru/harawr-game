#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

//TEXTURES
const int NULL_TEX = 0, // Error texture
          BRICK = 1,
          PLANK = 2,
          PLAYER = 10;

class Spritesheet
{
    public:
        Spritesheet(string path_to_file);

        sf::Sprite get_sprite(int id);

    private:
        sf::Texture spritesheet;
        vector<sf::Sprite> sprites;

        const int SIZE = 256;
        const int TILE_SIZE = 16;
};

#endif