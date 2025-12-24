#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "spritesheet.h"
#include "sound_system.h"
#include "button.h"

class MainMenu
{
    public:
        MainMenu(sf::RenderWindow &window, Spritesheet &spritesheet, SoundSystem &soundsystem, sf::Font &font);

        void draw();
        int update();

    private:
        sf::RenderWindow &window;
        Spritesheet &spritesheet;
        SoundSystem &soundsystem;
        sf::Font &font;

        vector<Button> buttons;
};

#endif