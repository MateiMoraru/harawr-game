#include "jumpscare.h"

vector<string> SCARY_PICTURES = {"assets/scary_jumpscare.png"};

Jumpscare::Jumpscare(SoundSystem &soundsystem, sf::RenderWindow &window, int display_id, sf::Vector2f position, int index) : soundsystem(soundsystem), window(window), display_image_id(display_id), position(position), index(index)
{
    sprite = sf::Sprite();
    sf::Texture texture;
    texture.loadFromFile("assets/spritesheet.png");
    sprite.setTexture(texture);
    sprite.setPosition(0, 0);

    sf::FloatRect bounds = sprite.getLocalBounds();
    float scalex = window.getSize().x / bounds.width;
    float scaley = window.getSize().y / bounds.height;
    sprite.setScale(scalex, scaley);
}

void Jumpscare::trigger()
{
    soundsystem.play_sound(JUMPSCARE_SOUND);
    triggered = true;
}

void Jumpscare::draw()
{
    if(triggered)
    {
        sprite.setColor(sf::Color(255, 255, 255, alpha));
        window.draw(sprite);
        alpha -= 5;

        if(alpha <= 0)
            triggered = false;
    }
}
