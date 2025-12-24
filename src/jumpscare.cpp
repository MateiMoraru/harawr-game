#include "jumpscare.h"

vector<string> SCARY_PICTURES = {"assets/sprites/freddy.png"};

Jumpscare::Jumpscare(SoundSystem &soundsystem, sf::RenderWindow &window, int display_id, sf::Vector2f position, int index) : soundsystem(soundsystem), window(window), display_image_id(display_id), position(position), index(index)
{
    texture.loadFromFile("assets/sprites/freddy.png");
    sprite.setTexture(texture);
    sprite.setScale(10.f, 10.f);
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
