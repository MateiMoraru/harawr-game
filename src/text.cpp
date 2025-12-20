#include <iostream>
#include "text.h"
using namespace std;

Text::Text(const std::string& fontPath, unsigned int size)
{
    if (fontPath.empty())
        throw std::runtime_error("Font path is empty");

    if (!font.loadFromFile(fontPath))
        throw std::runtime_error("Failed to load font: " + fontPath);

    text.setFont(font);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color::White);
}

void Text::set_string(const std::string& str) { text.setString(str); }
void Text::set_position(float x, float y) { text.setPosition(x, y); }
void Text::set_color(sf::Color color) { text.setFillColor(color); }
void Text::set_size(unsigned int char_size) { text.setCharacterSize(char_size); }

void Text::draw(sf::RenderWindow& window) { window.draw(text); }

sf::FloatRect Text::get_bounds() const { return text.getGlobalBounds(); }
