#include "audio.h"
#include <iostream>

std::map<std::string, Mix_Music*> Audio::music_map;

bool Audio::init() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Failed to initialize audio: " << Mix_GetError() << "\n";
        return false;
    }
    return true;
}

void Audio::quit() {
    for (auto& pair : music_map) {
        Mix_FreeMusic(pair.second);
    }
    music_map.clear();
    Mix_CloseAudio();
}

void Audio::load_music(const std::string& name, const std::string& path) {
    Mix_Music* music = Mix_LoadMUS(path.c_str());
    if (!music) {
        std::cerr << "Failed to load music: " << path << " - " << Mix_GetError() << "\n";
        return;
    }
    music_map[name] = music;
}

void Audio::play_music(const std::string& name, int loops) {
    auto it = music_map.find(name);
    if (it != music_map.end()) {
        Mix_PlayMusic(it->second, loops);
    }
}

void Audio::stop_music() {
    Mix_HaltMusic();
}