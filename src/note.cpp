#include "note.h"

Note::Note(sf::RenderWindow &window, Spritesheet &spritesheet, sf::Font &font, int number, sf::Vector2f position)
    : window(window),
      font(font),
      number(number),
      position(position),
      tile(spritesheet.get_sprite(BUTTON), BUTTON, {window.getSize().x * 0.1f, window.getSize().y * 0.1f}, {window.getSize().x * 0.8f, window.getSize().y * 0.8f})
{
    ifstream fin("assets/data/note_" + to_string(number) + ".txt");

    int i = 0;
    string str;
    while(getline(fin, str))
    {
        if(str.find_first_not_of(" \t\r") == std::string::npos)
            str = " ";

        Text line(font, 64);
        line.set_position(window.getSize().x / 5 + 16, window.getSize().y / 5 + 16 + 70 * i);
        line.set_string(str);
        line.set_color(sf::Color::Black);
        lines.push_back(line);
        i++;
    }
}

void Note::draw()
{
    tile.draw(window);
    for(Text &t : lines)
    {
        t.draw(window);
    }
}