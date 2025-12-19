#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace std;

int main()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    const int SCREEN_WIDTH = desktop.width, SCREEN_HEIGHT = desktop.height;

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML harawr game", sf::Style::Fullscreen);

    cout << "Created window (" << SCREEN_WIDTH << "; " << SCREEN_HEIGHT  << ")" << endl;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
                
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();

                if (event.key.code == sf::Keyboard::W)
                    std::cout << "W pressed\n";
            }
        }

        window.clear(sf::Color::Black);
        window.display();
    }

    return 0;
}
