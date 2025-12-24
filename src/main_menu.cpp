#include "main_menu.h"

MainMenu::MainMenu(sf::RenderWindow &window, Spritesheet &spritesheet, SoundSystem &soundsystem, sf::Font &font)
        : window(window),
          spritesheet(spritesheet),
          soundsystem(soundsystem),
          font(font)
{
    int centerx = window.getSize().x / 2;
    int centery = window.getSize().y / 2;

    int sizex = window.getSize().x / 2;
    int sizey = window.getSize().y / 20;

    Button start(window, soundsystem, spritesheet.get_sprite(BUTTON), sf::Vector2f(centerx - sizex / 2, centery / 3), sf::Vector2f(sizex, sizey), font);
    start.set_string("Start Game");
    buttons.push_back(start);

    Button quitb(window, soundsystem, spritesheet.get_sprite(BUTTON), sf::Vector2f(centerx - sizex / 2, centery * 1.66), sf::Vector2f(sizex, sizey), font);
    quitb.set_string("Quit");
    buttons.push_back(quitb);
}

void MainMenu::draw()
{
    for(Button &button : buttons)
    {
        button.draw();
    }
}

int MainMenu::update()
{
    for(int i = 0; i < buttons.size(); i++)
    {
        Button &button = buttons[i];
        button.update();
        if(button.pressed())
            return i + 1;
    }
    return 0;
}