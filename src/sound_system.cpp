#include "sound_system.h"

SoundSystem::SoundSystem()
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("assets/sfx/background_music.mp3")) {
        std::cerr << "Failed to load sound!" << std::endl;
    }

    sounds.push_back(buffer);

    if (!buffer.loadFromFile("assets/sfx/violin_abuse.mp3")) {
        std::cerr << "Failed to load sound!" << std::endl;
    }

    sounds.push_back(buffer);
}

void SoundSystem::play_sound(int id)
{
    activeSounds.emplace_back();
    sf::Sound &s = activeSounds.back();
    s.setBuffer(sounds[id]);
    s.play();

}


void SoundSystem::play_loop_sound(int id)
{
    loopedSound.setBuffer(sounds[id]);
    loopedSound.setLoop(true);
    loopedSound.play();
}
