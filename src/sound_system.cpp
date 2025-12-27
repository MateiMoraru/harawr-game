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
    looped.reserve(8);

    std::vector<string> filenames = {
        "assets/sfx/background_music.mp3",
        "assets/sfx/violin_abuse.mp3",
        "assets/sfx/footstep.mp3",
        "assets/sfx/door_open.mp3",
        "assets/sfx/key_pickup.mp3",
        "assets/sfx/click.mp3",
        "assets/sfx/door_knock.mp3",
        "assets/sfx/ear_ring.mp3",
        "assets/sfx/breathing.mp3",
        "assets/sfx/page_turn.mp3",
        "assets/sfx/jumpscare.mp3",
        "assets/sfx/haunt.mp3",
        "assets/sfx/dropping-rock.mp3"
    };

    for (auto &file : filenames)
    {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(file)) {
            std::cerr << "Failed to load sound: " << file << std::endl;
        }
        sounds.push_back(buffer);
    }
}

void SoundSystem::update()
{
    active_sounds.erase(
        std::remove_if(active_sounds.begin(), active_sounds.end(),
                       [](sf::Sound &s){ return s.getStatus() == sf::Sound::Stopped; }),
        active_sounds.end());
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
void SoundSystem::play_critical_sound(int id, float min, float max)
{
    critical_sounds.emplace_back();
    sf::Sound &s = critical_sounds.back();
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

void SoundSystem::reset_sounds()
{
    for(sf::Sound &sound : looped)
    {
        sound.stop();
    }
    for(sf::Sound &sound : active_sounds)
    {
        sound.stop();
    }
    looped.emplace_back();
    sf::Sound &s = looped.back();
    s.setBuffer(sounds[BACKGROUND_SOUND]);
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