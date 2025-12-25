#include "jumpscare.h"

vector<string> SCARY_PICTURES = {"assets/sprites/jumpscare_1.png"};

Jumpscare::Jumpscare(SoundSystem &soundsystem, sf::RenderWindow &window, int display_id, sf::Vector2f position, int index) : soundsystem(soundsystem), window(window), display_image_id(display_id), position(position), index(index)
{
    texture.loadFromFile(SCARY_PICTURES[0]);
    sprite.setTexture(texture);
    sprite.setScale(window.getSize().x / texture.getSize().x, window.getSize().y / texture.getSize().y);
}

void Jumpscare::trigger()
{
    soundsystem.play_sound(EAR_RING);
    soundsystem.play_sound(BREATHING);
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
