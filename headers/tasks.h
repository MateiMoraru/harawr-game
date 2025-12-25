#ifndef TASKS_H
#define TASKS_H

#include <SFML/Graphics.hpp>
#include <fstream>

#include "text.h"

class Tasks
{
    public:
        Tasks(sf::RenderWindow &window, sf::Font &font);

        void set_font(sf::Font &font) { this->font = font; }

        void draw();

    private:
        sf::RenderWindow &window;
        sf::Font &font;

        vector<Text> tasks;
};

#endif