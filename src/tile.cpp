#include "tile.h"

Tile::Tile(sf::Sprite sprite, int sprite_id)
{
    this->sprite = sprite;
    this->sprite_id = sprite_id;

    this->position = sf::Vector2f(0, 0);
    this->size = sf::Vector2f(32, 32);
}

Tile::Tile(sf::Sprite sprite, int sprite_id, const sf::Vector2f &position, const sf::Vector2f &size)
{
    this->sprite = sprite;
    this->sprite_id = sprite_id;

    this->position = position;
    this->size = size;

    this->sprite.setPosition(position);

    sf::IntRect rect = sprite.getTextureRect();

    sf::Vector2u tex_size(
        static_cast<unsigned>(rect.width),
        static_cast<unsigned>(rect.height)
    );


    this->sprite.setScale(
        size.x / tex_size.x,
        size.y / tex_size.y
    );
}

void Tile::draw(sf::RenderWindow &window, sf::RenderStates &states)
{
    window.draw(sprite, states);
}

sf::FloatRect Tile::get_global_bounds()
{
    return sf::FloatRect(position.x, position.y, size.x, size.y);
}


bool Tile::collides(const Tile& other) const
{
    return
        position.x < other.position.x + other.size.x &&
        position.x + size.x > other.position.x &&
        position.y < other.position.y + other.size.y &&
        position.y + size.y > other.position.y;
}

void Tile::set_sprite_color(sf::Color color)
{
    sprite.setColor(color);
}