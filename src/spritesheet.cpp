#include "spritesheet.h"

vector<int> collidable = {BRICK};

Spritesheet::Spritesheet()
{

    if(!spritesheet.loadFromFile("assets/sprites/spritesheet.png"))
    {
        cerr << "Failed to load from file" << endl;
        return;
    }

    for(int i = 0; i < SIZE; i += TILE_SIZE)
    {
        for(int j = 0; j < SIZE; j += TILE_SIZE)
        {
            sf::Sprite tile_sprite;
            tile_sprite.setTexture(spritesheet);
            tile_sprite.setTextureRect(sf::IntRect(j, i, TILE_SIZE, TILE_SIZE));
            sprites.push_back(tile_sprite);
        }
    }

}

void Spritesheet::draw(sf::RenderWindow &window)
{
    for(int i = 0; i < 8 * 8; i++)
    {
        sf::Sprite sprite = get_sprite(i);
        sprite.setPosition(i * 64, 100);
        sprite.setScale(4, 4);
        window.draw(sprite);
    }
}

sf::Sprite Spritesheet::get_sprite(int id)
{  
    return sprites[id];
}