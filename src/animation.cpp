#include "animation.h"

Animation::Animation(Spritesheet &spritesheet, int range, float rate, int start_id)
: spritesheet(spritesheet), range(range), rate(rate), start_frame(start_id), soundsystem(nullptr)
{
    clock = sf::Clock();
}

Animation::Animation(Spritesheet &spritesheet, int range, float rate, int start_id, SoundSystem &ss)
: spritesheet(spritesheet), range(range), rate(rate), start_frame(start_id), soundsystem(&ss)
{
    clock = sf::Clock();
}

void Animation::start()
{
    delta = sf::Time::Zero;
    clock.restart();
    current_sprite_id = start_frame;
    started = true;
}


void Animation::stop()
{
    started = false;
    passed = 0;
     
}

void Animation::update()
{
    if (!started)
    {
        clock.restart();
        return;
    }

    delta += clock.restart();

    if (delta.asSeconds() >= rate)
    {
        current_sprite_id =
            start_frame + (current_sprite_id - start_frame + 1) % range;

        delta -= sf::seconds(rate);
    }
}

void Animation::update(int id)
{
    if (!started)
    {
        clock.restart();
        return;
    }

    delta += clock.restart();

    if (delta.asSeconds() >= rate)
    {
        current_sprite_id =
            start_frame + (current_sprite_id - start_frame + 1) % range;

        delta -= sf::seconds(rate);
        if(passed % 3 == 0)
            soundsystem->play_sound(id, 0.5f, 2.f);
        passed++;
    }
}


