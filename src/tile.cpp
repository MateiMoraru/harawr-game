#include "tile.h"

Tile::Tile(sf::Sprite sprite, int sprite_id)
{
    this->sprite = sprite;
    this->sprite_id = sprite_id;

    this->position = sf::Vector2f(0, 0);
    this->size = sf::Vector2f(32, 32);
}

Tile::Tile(sf::Sprite sprite, int sprite_id, sf::Vector2f &position, sf::Vector2f &size)
{
    this->sprite = sprite;
    this->sprite_id = sprite_id;
    this->position = position;
    this->size = size;
}

void Tile::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}