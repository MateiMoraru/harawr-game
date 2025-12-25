#include "tasks.h"

Tasks::Tasks(sf::RenderWindow &window, sf::Font &font) : window(window), font(font)
{
    ifstream fin("assets/data/tasks.txt");

    Text text(font, 32);
    text.set_position(0, window.getSize().y * 0.1);
    text.set_string("Tasks:");
    tasks.push_back(text);

    text.set_string("");
    tasks.push_back(text);

    int i = 0;
    string str;
    while(getline(fin, str))
    {
        i++;
        text.set_string(to_string(i) + ". " + str);
        text.set_position(0, window.getSize().y * 0.1 + i * 32);
        tasks.push_back(text);
    }
}

void Tasks::draw()
{
    for(Text &text : tasks)
    {
        text.draw(window);
    }
}