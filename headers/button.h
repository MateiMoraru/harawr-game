#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "sound_system.h"
#include "tile.h"
#include "text.h"

class Button
{
    public:
        Button(sf::RenderWindow &window, SoundSystem &soundsystem, sf::Sprite sprite, sf::Vector2f position, sf::Vector2f size, sf::Font &font);

        void update();
        void draw();
        void set_string(const string &str);
        void set_position(float x, float y);

        bool pressed();

    private:
        sf::RenderWindow &window;
        SoundSystem &soundsystem;
        Tile tile;
        
        Text text;

        sf::Vector2f position, size;

        bool clicked = false;
        bool hovering = false;
};

#endif