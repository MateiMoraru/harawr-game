#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Text
{
private:
    sf::Text text;
    sf::Font font;

public:
    Text() {};
    Text(const std::string& fontPath, unsigned int size);
    void set_string(const std::string& str);
    void set_position(float x, float y);
    void set_color(sf::Color color);
    void set_size(unsigned int char_size);

    void draw(sf::RenderWindow& window);

    sf::FloatRect get_bounds() const;
};
