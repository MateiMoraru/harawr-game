#include "jumpscare.h"

vector<string> SCARY_PICTURES = {"assets/sprites/jumpscare_1.png"};

Jumpscare::Jumpscare(
    SoundSystem &soundsystem,
    sf::RenderWindow &window,
    int display_id,
    sf::Vector2f position,
    int index,
    Tile tile
)
    : soundsystem(soundsystem),
      window(window),
      display_image_id(display_id),
      position(position),
      index(index),
      tile(tile)
{
    // Load texture
    if (!texture.loadFromFile(SCARY_PICTURES[0]))
    {
        std::cerr << "Failed to load jumpscare texture\n";
    }
/*
    // Setup sprite
    sprite.setTexture(texture);
    sprite.setPosition(0.f, 0.f);
    sprite.setScale(
        static_cast<float>(window.getSize().x) / texture.getSize().x,
        static_cast<float>(window.getSize().y) / texture.getSize().y
    );

    // Create tile AFTER sprite is valid
    tile = Tile(
        sprite,
        -1,
        sf::Vector2f(0.f, 0.f),
        sf::Vector2f(window.getSize().x, window.getSize().y)
    );*/
}


void Jumpscare::trigger()
{
    alpha = 255;
    sprite.setColor(sf::Color(alpha, alpha, alpha, alpha)); // RESET
    soundsystem.play_critical_sound(EAR_RING, 0.7, 1.2);
    soundsystem.play_critical_sound(BREATHING, 0.7, 1.2);
    triggered = true;
}

void Jumpscare::draw()
{
    if (!triggered) return;

    tile.set_sprite_color(sf::Color(alpha, alpha, alpha, alpha));
    tile.draw(window);

    alpha -= 5;
    if (alpha <= 0)
        triggered = false;
}