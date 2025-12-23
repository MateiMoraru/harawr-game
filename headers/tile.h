#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class Tile
{
    public:
        Tile();
        Tile(sf::Sprite sprite, int sprite_id);
        Tile(sf::Sprite sprite, int sprite_id, const sf::Vector2f &position, const sf::Vector2f &size);

        void draw(sf::RenderWindow &window, sf::RenderStates &states);

        float get_x() const { return position.x; };
        float get_y() const { return position.y; };
        int get_id() const{ return sprite_id; };

        sf::FloatRect get_global_bounds();

        void set_position(float x, float y) { position = sf::Vector2f(x, y); sprite.setPosition(position); }
        void set_sprite(sf::Sprite sprite, int id) { this-> sprite = sprite; sprite_id = id; }

        bool collides(const Tile& other) const;

        void set_sprite_color(sf::Color color);

    private:
        sf::Sprite sprite;
        int sprite_id;

        sf::Vector2f position;
        sf::Vector2f size;
};

#endif