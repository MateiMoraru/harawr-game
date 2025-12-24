#include "player.h"

Player::Player(sf::RenderWindow &window, Spritesheet &spritesheet) : window(window), spritesheet(spritesheet), player(spritesheet.get_sprite(PLAYER), PLAYER)
{
    sf::Vector2u size = window.getSize();
    position = sf::Vector2f(size.x / 2 - (size.x / 2) % 64 - 64, size.y / 2 - (size.y / 2) % 64);
    player.set_position(position.x, position.y);
    Player::set_size(64.f, 64.f);
}

void Player::update()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        speed = 10.f;
    }
    else
    {
        speed = 5.f;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        move(0.f, -speed);
        moved.y = -speed; 
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        move(-speed, 0.f);
        moved.x = -speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        move(0.f, speed);
        moved.y = speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        move(speed, 0.f);
        moved.x = speed; 
    }

}

void Player::set_size(float x, float y)
{
    player.get_sprite().setScale(x / 16.f, y / 16.f);
}

void Player::move(float x, float y)
{
    position.x += x;
    position.y += y;

    player.set_position(position.x, position.y);
}

void Player::draw(sf::RenderStates states)
{
    window.draw(player.get_sprite(), states);
    //window.draw(circle_light);
}