#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>

#include "settings.h"
#include "tile.h"
#include "tile_map.h"
#include "spritesheet.h"
#include "text.h"
#include "player.h"
#include "sound_system.h"
#include "main_menu.h"

using namespace std;

float delta = 0;

//STATES
const int IN_GAME = 0,
          MAIN_MENU = 1;

int main()
{
    int state = MAIN_MENU;

    Settings settings = Settings();
    
    // Creating The Window

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    if(settings.get_fullscreen())
        settings.set_screen_size(desktop.width, desktop.height);
    const int SCREEN_WIDTH = settings.get_width(), SCREEN_HEIGHT = settings.get_height();

    sf::RenderWindow window;

    if(settings.get_fullscreen())
        window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML harawr game", sf::Style::Fullscreen);
    else
        window.create(sf::VideoMode(settings.get_width(), settings.get_height()), "SFML harawr game");
    cout << "Created window (" << SCREEN_WIDTH << "; " << SCREEN_HEIGHT  << ")" << endl;

    // Loading Settings
    if(!settings.get_vsync())
        window.setFramerateLimit(settings.get_fps());
    else 
        window.setVerticalSyncEnabled(settings.get_vsync());

    Spritesheet spritesheet = Spritesheet();
    SoundSystem soundsystem = SoundSystem();
    Player player = Player(window, spritesheet, soundsystem);
    TileMap tile_map = TileMap(window, spritesheet, soundsystem);
    
    sf::Clock clock;
    int frames = 0;

    sf::Font font;
    font.loadFromFile("assets/font/pixelated.ttf");

    Text fps_text = Text(font, 32);
    fps_text.set_position(0, 0);

    MainMenu main_menu(window, spritesheet, soundsystem, font);

    //Main Loop

    sf::RenderStates states;

    soundsystem.play_loop_sound(BACKGROUND_SOUND);

    int menu_return = -1;

    while (window.isOpen())
    {
        frames++;
        if (clock.getElapsedTime().asSeconds() >= 1.f)
        {
            fps_text.set_string("FPS: " + std::to_string(frames));
            frames = 0;
            clock.restart();
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    state = MAIN_MENU;
                if (event.key.code == sf::Keyboard::P)
                    tile_map.save();
            }
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                {
                    float delta = event.mouseWheelScroll.delta;

                    if (delta > 0)
                        tile_map.scroll(1);
                    else if (delta < 0)
                        tile_map.scroll(-1);
                }
            }
        }
        window.clear(sf::Color::Black);

        if(state == IN_GAME)
        {
            tile_map.update(player);
            player.update();
            
            player.offset.x = player.get_x() - SCREEN_WIDTH / 2.f;
            player.offset.y = player.get_y() - SCREEN_HEIGHT / 2.f;

            states.transform = sf::Transform();
            states.transform.translate(-player.get_x_offset(), -player.get_y_offset());
            

            tile_map.draw(player, states);

            player.draw(states);

            tile_map.draw_jumpscares(player);

            tile_map.draw_overlay();

            Tile temp_tile = Tile(spritesheet.get_sprite(tile_map.get_selected_block()), tile_map.get_selected_block(), {0, 100}, sf::Vector2f(64, 64));
            temp_tile.draw(window);
        }
        else if(state == MAIN_MENU)
        {
            menu_return = main_menu.update();
            main_menu.draw();

            if(menu_return == 1)
                state = IN_GAME;
            else if(menu_return == 2)
                window.close();
        }

        fps_text.draw(window);

        window.display();
    }

    return 0;
}
