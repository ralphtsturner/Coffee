#include "audio.h"
#include <iostream>

std::map<std::string, Mix_Chunk*> Audio::sound_map;
std::map<std::string, Mix_Music*> Audio::music_map;

std::vector<std::string> Audio::music_sequence;
size_t Audio::current_track = 0;

bool Audio::init() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! Error: " << Mix_GetError() << "\n";
        return false;
    }
    return true;
}

void Audio::quit() {
    for (auto& pair : sound_map) {
        Mix_FreeChunk(pair.second);
    }
    for (auto& pair : music_map) {
        Mix_FreeMusic(pair.second);
    }
    sound_map.clear();
    music_map.clear();
    Mix_CloseAudio();
}

void Audio::load_music(const std::string& name, const std::string& path) {
    Mix_Music* new_music = Mix_LoadMUS(path.c_str());
    if (!new_music) {
        std::cerr << "Failed to load music: " << path << " Error: " << Mix_GetError() << "\n";
        return;
    }
    music_map[name] = new_music;
}

void Audio::play_music(const std::string& name, int loops) {
    auto it = music_map.find(name);
    if (it != music_map.end()) {
        if (Mix_PlayMusic(it->second, loops) == -1) {
            std::cerr << "Error playing music: " << Mix_GetError() << "\n";
        }
    } else {
        std::cerr << "Music not found: " << name << "\n";
    }
}

void Audio::pause_music() {
    Mix_PauseMusic();
}

void Audio::resume_music() {
    Mix_ResumeMusic();
}

void Audio::stop_music() {
    Mix_HaltMusic();
}

void Audio::load_sound(const std::string& name, const std::string& path) {
    Mix_Chunk* new_sound = Mix_LoadWAV(path.c_str());
    if (!new_sound) {
        std::cerr << "Failed to load sound: " << path << " Error: " << Mix_GetError() << "\n";
        return;
    }
    sound_map[name] = new_sound;
}

void Audio::play_sound(const std::string& name, int loops) {
    auto it = sound_map.find(name);
    if (it != sound_map.end()) {
        Mix_PlayChannel(-1, it->second, loops);
    } else {
        std::cerr << "Sound not found: " << name << "\n";
    }
}

void Audio::set_music_sequence(const std::vector<std::string>& sequence) {
    music_sequence = sequence;
    current_track = 0;
    play_next_track();
}

void Audio::set_music_sequence(std::initializer_list<std::string> sequence) {
    music_sequence = sequence;
    current_track = 0;
    play_next_track();
}

void Audio::play_next_track() {
    if (music_sequence.empty()) return;

    const std::string& next_track = music_sequence[current_track];
    play_music(next_track, 1); // Play current track once

    Mix_HookMusicFinished([]() {
        current_track = (current_track + 1) % music_sequence.size();
        Audio::play_next_track();
    });
}
