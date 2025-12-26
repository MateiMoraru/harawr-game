#ifndef NUN_H
#define NUN_H

#include <cmath>

#include "spritesheet.h"
#include "sound_system.h"
#include "tile.h"
#include "player.h"

class Nun
{
    public:
        Nun(sf::RenderWindow &window, Spritesheet &spritesheet, SoundSystem &soundsystem, sf::Vector2f position, sf::Vector2f size);

        void update(Player &player);
        void draw(sf::RenderStates &states, sf::Color color);
        void move(float x, float y);
        bool collides(vector<Tile> &collidable_tile);

        bool is_active() const { return active; }
        float get_x() const { return position.x; }
        float get_y() const { return position.y; }
        float get_distance() const { return distance; }
        sf::Vector2f get_direction() const { return direction; }
        float get_speed() const { return speed; }

        void set_active(bool activated) { active = activated; }
    private:
        sf::RenderWindow &window;
        Spritesheet &spritesheet;
        SoundSystem &soundsystem;

        sf::Vector2f position;
        sf::Vector2f size;
        sf::Vector2f direction;
        Tile nun;
        float distance = 1000.f;
        float speed = 250.f;

        bool active = false;
};

#endif