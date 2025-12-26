#ifndef NOTE_H
#define NOTE_H

#include <fstream>
#include <iostream>
#include <cstring>

#include "spritesheet.h"
#include "text.h"
#include "tile.h"

class Note
{
    public:
        Note();
        Note(sf::RenderWindow &window, Spritesheet &spritesheet, sf::Font &font, int number, sf::Vector2f position);

        float get_x() const { return position.x; }
        float get_y() const { return position.y; }
        int get_id() const { return number; }
        bool is_displayed() const { return displaying; }


        void draw();
        void display() { displaying = true; };

    private:
        sf::RenderWindow &window;
        sf::Font &font;
        Tile tile;

        sf::Vector2f position;
        int number;
        vector<string> text;
        vector<Text> lines;
        bool displaying = false;
};

#endif