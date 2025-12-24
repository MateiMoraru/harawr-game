#pragma once

#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

using namespace std;

const int BACKGROUND_SOUND = 0,
          JUMPSCARE_SOUND = 1,
          FOOTSTEP = 2;

class SoundSystem
{
    public:
        SoundSystem();
        void play_sound(int id);
        void play_loop_sound(int id);
        void play_sound(int id, float min, float max);

        float random_float(float min, float max);

    private:
        vector<sf::SoundBuffer> sounds;
        vector<sf::Sound> looped;
        vector<sf::Sound> active_sounds;

};


#endif