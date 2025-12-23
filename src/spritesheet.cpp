#include "spritesheet.h"

Spritesheet::Spritesheet()
{

    if(!spritesheet.loadFromFile("assets/spritesheet.png"))
    {
        cerr << "Failed to load from file" << endl;
        return;
    }

    sf::Sprite sprite;
    sprite.setTexture(spritesheet);

    for(int i = 0; i < SIZE; i += TILE_SIZE)
    {
        for(int j = 0; j < SIZE; j += TILE_SIZE)
        {
            sprite.setTextureRect(sf::IntRect(j, i, TILE_SIZE, TILE_SIZE));
            sprites.push_back(sprite);
        }
    }
}

sf::Sprite Spritesheet::get_sprite(int id)
{  
    return sprites[id];
}