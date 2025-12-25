#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <algorithm>

#include "tile.h"
#include "spritesheet.h"
#include "player.h"
#include "jumpscare.h"
#include "door.h"
#include "note.h"

using namespace std;

class TileMap
{
    public:
        TileMap(sf::RenderWindow &window, Spritesheet &spritesheet, SoundSystem &soundsystem);

        void update(Player &player, float delta_time);
        void draw(Player &player, sf::RenderStates &states, float delta_time);
        void draw_overlay();
        void draw_jumpscares(Player &player);
        void draw_notes(Player &player);

        void save();
        void load(SoundSystem &soundsystem);

        void scroll(int delta);

        int get_selected_block() const { return selected_tile_id; }

    private:
        sf::RenderWindow& window;
        Spritesheet& spritesheet;
        SoundSystem &soundsystem;

        sf::Font font;
        sf::RectangleShape thick_line;

        int tile_size = 64;

        bool is_editing = true;
        bool left_mouse_was_pressed = false;
        int selected_tile_id = 0;
        float elapsed_time_door_knock = 0;

        vector<Tile> tile_map;
        vector<Tile> collidable_tiles;
        vector<Tile> keys;
        vector<Jumpscare> jumpscares;
        vector<Door> doors;
        vector<Note> notes;
        vector<pair<float, float>> line_overlay;

};

#endif