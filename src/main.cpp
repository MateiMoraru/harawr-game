#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <thread>

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
    sf::Clock clock;
    sf::Clock delta_clock;
    sf::Clock fps_clock; 
    int state = MAIN_MENU;

    Settings settings = Settings();

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

    if(!settings.get_vsync())
    {
        cout << "Vsync disabled" << endl;
        window.setVerticalSyncEnabled(false);
        window.setFramerateLimit(settings.get_fps());
    }
    else 
        window.setVerticalSyncEnabled(true);

    sf::Mouse::setPosition({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});

    Spritesheet spritesheet = Spritesheet();
    SoundSystem soundsystem = SoundSystem();
    Player player = Player(window, spritesheet, soundsystem);
    TileMap tile_map = TileMap(window, spritesheet, soundsystem);
    
    int frames = 0;

    sf::Font font;
    font.loadFromFile("assets/font/pixelated.ttf");

    MainMenu main_menu(window, spritesheet, soundsystem, font);

    Text fps_text = Text(font, 32);
    fps_text.set_position(0, 100);
    Text display_message(font, 32);
    display_message.set_position(0, SCREEN_HEIGHT * 0.9f);

    sf::RenderStates states;

    soundsystem.play_loop_sound(BACKGROUND_SOUND);

    int menu_return = -1;
    cout << "Elapsed loading time: " << clock.getElapsedTime().asSeconds() << "s" << endl;
    Tile temp_tile;
    float delta_time = 0;
    float display_message_timer = 0;
    bool displayed_last_message = false;

    while (window.isOpen())
    {
        float delta_time = delta_clock.restart().asSeconds();
        frames++;

        if (fps_clock.getElapsedTime().asSeconds() >= 1.f)
        {
            fps_text.set_string("FPS: " + std::to_string(frames));
            frames = 0;
            fps_clock.restart();
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
            if(!tile_map.update(player, delta_time))
            {
                state = MAIN_MENU;
                display_message.set_string("Commit dieded");
                display_message_timer = 0.f;

                soundsystem.reset_sounds();
                soundsystem.play_loop_sound(BACKGROUND_SOUND);
                player.remove_keys();
                tile_map.restart();
            }
            player.update(delta_time);

            player.offset.x = player.get_x() - SCREEN_WIDTH / 2.f;
            player.offset.y = player.get_y() - SCREEN_HEIGHT / 2.f;

            states.transform = sf::Transform();
            states.transform.translate(-player.get_x_offset(), -player.get_y_offset());

            tile_map.draw(player, states, delta_time);
            player.draw(states);
            tile_map.draw_keys(player, states);
            tile_map.draw_jumpscares(player);
            if(random_float(0, 1) >= 0.995)
                tile_map.draw_overlay();
            tile_map.draw_notes(player);
            tile_map.draw_tasks();

            temp_tile.set_sprite(spritesheet.get_sprite(tile_map.get_selected_block()), tile_map.get_selected_block());
            temp_tile.draw(window);

            if(tile_map.get_end())
            {
                tile_map.draw_end();
                display_message.set_string("Finally dealt with it.");
                display_message_timer = -5.f;
            }

            if(!displayed_last_message && player.get_x() > 5760 - player.get_x_offset() && player.get_x () > -3072 - player.get_y_offset())
            {
                cout << "AAAAAAA" << endl;
                display_message.set_string("Hang yourself.");
                displayed_last_message = true;
                display_message_timer = 0.0f;
            }
        }

        else if(state == MAIN_MENU)
        {
            menu_return = main_menu.update();
            main_menu.draw();

            if(menu_return == 1)
            {
                state = IN_GAME;
                if(!player.is_alive())
                {
                    player.revive();
                    player.set_position(tile_map.get_checkpoint().get_x(), tile_map.get_checkpoint().get_y());
                    tile_map.restart_nuns();
                }
            }
            else if(menu_return == 2)
                window.close();
        }

        window.setView(window.getDefaultView());
        fps_text.draw(window);

        display_message.draw(window);
        if(display_message.get_string() != "")
        {
            display_message_timer += delta_time;
            if(display_message_timer >= 5.f)
            {
                display_message.set_string("");
                display_message_timer = 0;
            }
        }

        window.display();
    }

    return 0;
}
