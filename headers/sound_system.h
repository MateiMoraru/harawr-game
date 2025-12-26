#pragma once

#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

using namespace std;

const int BACKGROUND_SOUND = 0,
          JUMPSCARE_SOUND = 1,
          FOOTSTEP = 2,
          DOOR_OPEN = 3,
          KEY_PICKUP = 4,
          CLICK = 5,
          DOOR_KNOCK = 6,
          EAR_RING = 7,
          BREATHING = 8,
          PAGE_TURN = 9,
          JUMPSCARE = 10,
          HAUNT = 11,
          DROPPING_ROCK = 12;

class SoundSystem
{
    public:
        SoundSystem();
        ~SoundSystem();

        void play_sound(int id);
        void play_loop_sound(int id);
        void play_sound(int id, float min, float max);
        void play_critical_sound(int id, float min, float max);
        void update();
        void reset_sounds();

        float random_float(float min, float max);

        vector<sf::Sound> get_looped() const { return looped; }

    private:
        vector<sf::SoundBuffer> sounds;
        vector<sf::Sound> looped;
        vector<sf::Sound> active_sounds;
        vector<sf::Sound> critical_sounds;


};


#endif