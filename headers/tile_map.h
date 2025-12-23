#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <iostream>
#include <vector>
#include <fstream>

#include "tile.h"
#include "spritesheet.h"
#include "player.h"

using namespace std;

class TileMap
{
    public:
        TileMap(sf::RenderWindow &window, Spritesheet &spritesheet);

        void update(Player &player);
        void draw(Player &player, sf::RenderStates &states);
        void draw_overlay();

        void save();
        void load();

        void scroll(int delta);

    private:
        sf::RenderWindow& window;
        Spritesheet& spritesheet;

        sf::RectangleShape thick_line;

        int tile_size = 64;

        bool is_editing = true;
        bool left_mouse_was_pressed = false;
        int selected_tile_id = 0;

        vector<Tile> tile_map;
        vector<pair<float, float>> line_overlay;
};

#endif