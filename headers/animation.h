#ifndef ANIMATION_H
#define ANIMATION_H

#include "spritesheet.h"
#include "sound_system.h"

class Animation
{
    public:
        Animation(Spritesheet &spritesheet, int range, float rate, int start_id);
        Animation(Spritesheet &spritesheet, int range, float rate, int start_id, SoundSystem &soundsystem);

        void update();
        void update(int id);

        void start();
        void stop();

        sf::Sprite get_sprite() const { return spritesheet.get_sprite(current_sprite_id); } 
        bool get_started() const { return started; }

    private:
        Spritesheet &spritesheet;
        SoundSystem* soundsystem = nullptr;

        sf::Clock clock;
        sf::Time delta;
        sf::Sprite current_sprite;

        int start_frame;
        int current_sprite_id;

        int range;
        float rate;
        int passed = 0;

        bool started = false;
};

#endif