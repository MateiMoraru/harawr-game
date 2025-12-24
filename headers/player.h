#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>

#include "tile.h"
#include "spritesheet.h"
#include "animation.h"

using namespace std;

class Player
{
    public:
        Player(sf::RenderWindow &window, Spritesheet &spritesheet, SoundSystem &soundsystem);
        
        sf::Vector2f offset;

        void draw(sf::RenderStates states);
        void update();

        void move(float x, float y);

        // fucking getters
        float get_x() const { return position.x; }
        float get_y() const { return position.y; }
        float get_x_offset() const { return offset.x; }
        float get_y_offset() const { return offset.y; }
        int get_size() const { return size; }
        float get_speed() const { return speed; }
        sf::Vector2f get_moved() const { return moved; }
        sf::Sprite get_sprite() const { return player.get_sprite(); }
        sf::FloatRect get_hitbox() const { return hitbox; }

        bool has_in_inventory(int id) const { return find(inventory.begin(), inventory.end(), id) != inventory.end(); }

        void set_size(float x, float y);
        void add_key(int id);

    private:
        sf::RenderWindow& window;
        Spritesheet& spritesheet;

        Animation walk_animation_up, walk_animation_down, walk_animation_left, walk_animation_right;
        sf::FloatRect hitbox;
        
        Tile player;
        
        int size = 64 * .9f;
        
        sf::Vector2f moved;
        sf::Vector2f position;
        float speed = 8.f;

        vector<int> inventory;

};

#endif