#include "sound_system.h"

SoundSystem::SoundSystem()
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("assets/background_music.mp3")) {
        std::cerr << "Failed to load sound!" << std::endl;
    }

    sounds.push_back(buffer);
}

void SoundSystem::play_sound(int id)
{
    sf::Sound sound;
    sound.setBuffer(sounds[id]);
    sound.play();
    activeSounds.push_back(sound);
}


void SoundSystem::play_loop_sound(int id)
{
    loopedSound.setBuffer(sounds[id]);
    loopedSound.setLoop(true);
    loopedSound.play();
}
