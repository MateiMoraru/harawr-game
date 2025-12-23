#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

using namespace std;

const int BACKGROUND_SOUND = 0,
          JUMPSCARE_SOUND = 1;

class SoundSystem
{
    public:
        SoundSystem();
        void play_sound(int id);
        void play_loop_sound(int id);

    private:
        std::vector<sf::SoundBuffer> sounds;
        std::vector<sf::Sound> activeSounds;
        sf::Sound loopedSound;
};


#endif