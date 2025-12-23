#include "player.h"

Player::Player(sf::RenderWindow &window, Spritesheet &spritesheet) : window(window), spritesheet(spritesheet), player(spritesheet.get_sprite(PLAYER), PLAYER)
{
    sf::Vector2u size = window.getSize();
    position = sf::Vector2f(size.x / 2 - (size.x / 2) % 64 - 64, size.y / 2 - (size.y / 2) % 64);
}

void Player::update()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        move(0.f, -speed);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        move(-speed, 0.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        move(0.f, speed);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        move(speed, 0.f);
    }
}

void Player::move(float x, float y)
{
    position.x += x;
    position.y += y;

    player.set_position(position.x, position.y);
}

void Player::draw()
{
    //window.draw(player);
    //window.draw(circle_light);
}