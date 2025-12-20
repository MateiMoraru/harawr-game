#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class Tile
{
    public:
        Tile(sf::Sprite sprite, int sprite_id);
        Tile(sf::Sprite sprite, int sprite_id, const sf::Vector2f &position, const sf::Vector2f &size);

        void draw(sf::RenderWindow &window);

        bool collides(const Tile& other) const;

    private:
        sf::Sprite sprite;
        int sprite_id;

        sf::Vector2f position;
        sf::Vector2f size;
};

#endif