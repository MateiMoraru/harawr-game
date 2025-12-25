#include "note.h"

Note::Note(sf::RenderWindow &window, Spritesheet &spritesheet, sf::Font &font, int number)
    : window(window),
      font(font),
      number(number),
      tile(Tile(spritesheet.get_sprite(BUTTON), BUTTON, sf::Vector2f(window.getSize().x / 5, window.getSize().y / 5), sf::Vector2f(window.getSize().x / 5 * 4, window.getSize().y / 5)))

{
    ifstream fin("assets/data/note_" + to_string(number) + ".txt");

    int i = 0;
    string str;
    while(getline(fin, str))
    {
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
    for(Text t : lines)
    {
        t.draw(window);
    }
}