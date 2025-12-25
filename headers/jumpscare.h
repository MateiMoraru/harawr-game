#ifndef JUMPSCARE_H
#define JUMSCARE_H

#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "sound_system.h"
#include "spritesheet.h"

using namespace std;

extern std::vector<std::string> SCARY_PICTURES;


class Jumpscare
{
    public:
        Jumpscare(SoundSystem &soundsystem, sf::RenderWindow &window, int display_id, sf::Vector2f position, int index);

        void trigger();
        void draw();

        float get_x() const { return position.x; }
        float get_y() const { return position.y; }
        int get_index() const { return index; }
        int get_id() const { return display_image_id; }
        bool is_triggered() const { return triggered; }
        bool is_expired() const { return alpha < 250; }
        bool is_deleted() const { return deleted; }

        void delete_() { deleted = true;}

    private:
        SoundSystem &soundsystem;
        sf::RenderWindow &window;
    
        int index;
        int display_image_id;
        int alpha = 255;
        bool triggered = false;
        bool deleted = false;
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f position;

};

#endif