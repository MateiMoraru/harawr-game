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
#include "tasks.h"
#include "nun.h"

using namespace std;

float random_float(float min, float max);

class TileMap
{
    public:
        TileMap(sf::RenderWindow &window, Spritesheet &spritesheet, SoundSystem &soundsystem);

        bool update(Player &player, float delta_time);
        void draw(Player &player, sf::RenderStates &states, float delta_time);
        void draw_overlay();
        void draw_jumpscares(Player &player);
        void draw_notes(Player &player);
        void draw_keys(Player &player, sf::RenderStates &states);
        void draw_tasks();
        void draw_end();

        void save();
        void load(SoundSystem &soundsystem, Tile end_picture);

        void restart_nuns();
        void restart();
        void scroll(int delta);

        int get_selected_block() const { return selected_tile_id; }
        Tile get_checkpoint() const { return checkpoint; }
        bool get_end() const { return end; }

    private:
        sf::RenderWindow& window;
        Spritesheet& spritesheet;
        SoundSystem &soundsystem;

        sf::Font font;
        sf::RectangleShape thick_line;
        Tasks tasks;
        Tile checkpoint;
        sf::Sprite end_sprite;
        sf::Texture end_texture;
        Tile end_picture;

        int tile_size = 64;

        bool is_editing = true;
        bool left_mouse_was_pressed = false;
        bool end = false;
        int selected_tile_id = 0;
        float elapsed_time_door_knock = 0;
        int haunt_sound_index = -1;

        vector<Tile> tile_map;
        vector<Tile> collidable_tiles;
        vector<Tile> keys;
        vector<Tile> keys_start;
        vector<Jumpscare> jumpscares;
        vector<Door> doors;
        vector<Note> notes;
        vector<Nun> nuns;
        vector<Nun> nuns_start;
        vector<Tile> checkpoints;
        vector<pair<float, float>> line_overlay;

};

#endif