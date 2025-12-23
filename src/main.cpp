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

using namespace std;

int main()
{
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

    Spritesheet spritesheet = Spritesheet("assets/spritesheet.png");

    TileMap tile_map = TileMap(window, spritesheet);
    
    sf::Clock clock;
    int frames = 0;

    Text text = Text("assets/arial.ttf", 32);
    text.set_position(32, 32);

    Player player = Player(window, spritesheet);

    //Main Loop

    sf::RenderStates states;

    while (window.isOpen())
    {
        frames++;
        if (clock.getElapsedTime().asSeconds() >= 1.f)
        {
            cout << frames << endl;
            text.set_string("FPS: " + std::to_string(frames));
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
                    window.close();
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

        tile_map.update(player);
        player.update();
        
        player.offset.x = player.get_x() - SCREEN_WIDTH / 2.f;
        player.offset.y = player.get_y() - SCREEN_HEIGHT / 2.f;

        states.transform = sf::Transform();
        states.transform.translate(-player.get_x_offset(), -player.get_y_offset());
        
        window.clear(sf::Color::Black);

        tile_map.draw(player, states);
        tile_map.draw_overlay();


        text.draw(window);

        window.display();
    }

    return 0;
}
