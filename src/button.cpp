#include "button.h"

Button::Button(sf::RenderWindow &window, SoundSystem &soundsystem, sf::Sprite sprite, sf::Vector2f position, sf::Vector2f size, sf::Font &font)
      : window(window),
        soundsystem(soundsystem),
        tile(tile),
        position(position),
        size(size),
        text(font, 32)
{
    sprite.setScale(size.x / 16, size.y / 16);
    sprite.setPosition(position);

    tile.set_sprite(sprite, 24);
    tile.set_position(position.x, position.y);
    tile.set_scale(sf::Vector2f(size.x / 16, size.y / 16));
    
    text.set_string("");
    text.set_color(sf::Color::Black);
}

void Button::set_string(const string &str)
{
    text.set_string(str);

    sf::FloatRect bounds = text.get_bounds();

    float textx = position.x + (size.x - bounds.width) / 2.f - bounds.left - bounds.width / 4;

    float texty = position.y + (size.y - bounds.height) / 2.f - bounds.top;

    text.set_position(textx, texty);
}

void Button::set_position(float x, float y)
{
    position.x = x;
    position.y = y;
}

void Button::update()
{
    sf::Vector2i mouse = sf::Mouse::getPosition(window);

    hovering = mouse.x > position.x && mouse.x < position.x + size.x && mouse.y > position.y && mouse.y < position.y + size.y;
    if(hovering)
        tile.set_sprite_color(sf::Color(100, 100, 100, 100));
    else
        tile.set_sprite_color(sf::Color(255, 255, 255, 255));
}

void Button::draw()
{
    tile.draw(window);
    if(text.get_string() != "")
        text.draw(window);
}

bool Button::pressed()
{
    if(hovering && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        soundsystem.play_sound(CLICK);
        return true;
    }
    return false;
}