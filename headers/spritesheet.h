#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

//TEXTURES
const int NULL_TEX = 64, // Error texture
          FLOOR = 1,
          BRICK = 2,
          JUMPSCARE_BLOCK = 3,
          DOOR_YELLOW = 4,
          DOOR_BLUE = 5,
          DOOR_RED = 6,
          DOOR_GREEN = 7,
          PLAYER = 8,
          PLAYER_UP_1 = 9,
          PLAYER_UP_2 = 10,
          PLAYER_DOWN = 11,
          PLAYER_DOWN_1 = 12,
          PLAYER_DOWN_2 = 13,
          KEY_YELLOW = 14,
          KEY_BLUE = 15,
          PLAYER_LEFT = 16,
          PLAYER_LEFT_1 = 17,
          PLAYER_LEFT_2 = 18,
          PLAYER_RIGHT = 19,
          PLAYER_RIGHT_1 = 20,
          PLAYER_RIGHT_2 = 21,
          KEY_RED = 22,
          KEY_GREEN = 23,
          BUTTON = 24,
          PLANKS = 25,
          NUN_LEFT = 26,
          NUN_RIGHT = 27,
          NUN_UP = 28,
          NUN_DOWN = 29,
          BLUE_WALL = 30,
          WALL = 31,
          CHECKPOINT = 32;

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

        const int SIZE = 128;
        const int TILE_SIZE = 16;
};

#endif