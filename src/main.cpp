#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>

#include "settings.h"
#include "tile.h"
#include "tile_map.h"
#include "spritesheet.h"
#include "text.h"

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

    //Tile null_tile = Tile(spritesheet.get_sprite(0), 0, sf::Vector2f(0, 0), sf::Vector2f(128, 128));
    TileMap tile_map = TileMap(window, spritesheet);

    //Main Loop

    sf::Clock clock;
    float fps = 0.f;

    Text text = Text("assets/arial.ttf", 32);
    text.set_position(32, 32);

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        fps = 1.f / dt.asSeconds();
        text.set_string(to_string(fps));

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
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

        tile_map.update();

        window.clear(sf::Color::Black);

        tile_map.draw();
        text.draw(window);

        window.display();
    }

    return 0;
}
