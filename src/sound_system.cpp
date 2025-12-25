#include "sound_system.h"
#include <random>

float SoundSystem::random_float(float min, float max)
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rng);
}

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

    if (!buffer.loadFromFile("assets/sfx/footstep.mp3")) {
        std::cerr << "Failed to load sound!" << std::endl;
    }

    sounds.push_back(buffer);

    if (!buffer.loadFromFile("assets/sfx/door_open.mp3")) {
        std::cerr << "Failed to load sound!" << std::endl;
    }

    sounds.push_back(buffer);

    if (!buffer.loadFromFile("assets/sfx/key_pickup.mp3")) {
        std::cerr << "Failed to load sound!" << std::endl;
    }

    sounds.push_back(buffer);

    if (!buffer.loadFromFile("assets/sfx/click.mp3")) {
        std::cerr << "Failed to load sound!" << std::endl;
    }

    sounds.push_back(buffer);
}

void SoundSystem::play_sound(int id)
{
    active_sounds.emplace_back();
    sf::Sound &s = active_sounds.back();
    s.setBuffer(sounds[id]);
    s.play();

}

void SoundSystem::play_sound(int id, float min, float max)
{
    active_sounds.emplace_back();
    sf::Sound &s = active_sounds.back();
    s.setBuffer(sounds[id]);
    s.setPitch(random_float(min, max));
    s.play();

}

void SoundSystem::play_loop_sound(int id)
{
    looped.emplace_back();
    sf::Sound &s = looped.back();
    s.setBuffer(sounds[id]);
    s.play();
    s.setLoop(true);
}

SoundSystem::~SoundSystem()
{
    for (auto& s : active_sounds)
        s.stop();

    for (auto& s : looped)
        s.stop();

    active_sounds.clear();
    looped.clear();
}