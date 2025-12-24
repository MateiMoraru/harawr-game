#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace std;

class Text
{

    public:
        Text() {};
        Text(const sf::Font &font, unsigned int size);

        string get_string() const { return str; }

        void set_string(const string& str);
        void set_position(float x, float y);
        void set_color(sf::Color color);
        void set_size(unsigned int char_size);

        void draw(sf::RenderWindow& window);

        sf::FloatRect get_bounds() const;

    private:
        sf::Text text;
        sf::Font font;

        string str;
};
