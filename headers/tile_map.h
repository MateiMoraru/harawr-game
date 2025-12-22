#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <iostream>
#include <vector>

#include "tile.h"
#include "spritesheet.h"

using namespace std;

class TileMap
{
    public:
        TileMap(sf::RenderWindow &window, Spritesheet &spritesheet);

        void update();
        void draw();
        void draw_overlay();

        void scroll(int delta);

    private:
        sf::RenderWindow& window;
        Spritesheet& spritesheet;

        int tile_size = 32;

        bool is_editing = true;
        bool left_mouse_was_pressed = false;
        int selected_tile_id = 0;

        vector<Tile> tile_map;
        vector<pair<float, float>> line_overlay;
};

#endif