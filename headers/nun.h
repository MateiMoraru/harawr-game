#ifndef NUN_H
#define NUN_H

#include <cmath>
#include <algorithm>
#include <iostream>

#include "spritesheet.h"
#include "sound_system.h"
#include "tile.h"
#include "player.h"

using namespace std;

class Nun
{
    public:
        Nun(sf::RenderWindow &window, Spritesheet &spritesheet, SoundSystem &soundsystem, sf::Vector2f position, sf::Vector2f size);

        void update(Player &player, float delta_time);
        void draw(sf::RenderStates &states, sf::Color color);
        void move(float x, float y);
        void restart();

        bool is_active() const { return active; }
        bool collides(vector<Tile> &collidable_tile);
        float get_x() const { return position.x; }
        float get_y() const { return position.y; }
        float get_distance() const { return distance; }
        sf::Vector2f get_direction() const { return direction; }
        float get_speed() const { return speed; }
        sf::FloatRect get_global_bounds() const { return nun.get_sprite().getGlobalBounds(); }

        void set_active(bool activated) { active = activated; }

    private:
        sf::RenderWindow &window;
        Spritesheet &spritesheet;
        SoundSystem &soundsystem;

        sf::Vector2f position;
        sf::Vector2f start_position;
        sf::Vector2f size;
        sf::Vector2f direction;
        Tile nun;
        float distance = 1000.f;
        float speed = 250.f;
        float dt = 0;
        vector<sf::Vector2f> positions;
        float fly_dir = 1;
        bool active = false;
};

#endif