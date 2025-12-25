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
        Note(sf::RenderWindow &window, Spritesheet &spritesheet, sf::Font &font, int number);

        void draw();

    private:
        sf::RenderWindow &window;
        sf::Font &font;
        Tile tile;

        int number;
        vector<string> text;
        vector<Text> lines;
};

#endif