#include "audio.h"
#include <iostream>

// Define static members
std::map<std::string, Mix_Music*> Audio::music_map;
std::map<std::string, Mix_Chunk*> Audio::sound_map;

bool Audio::init(int frequency, Uint16 format, int channels, int chunksize) {
    if (Mix_OpenAudio(frequency, format, channels, chunksize) == -1) {
        std::cerr << "Failed to open audio: " << Mix_GetError() << "\n";
        return false;
    }

    // Initialize any required formats (e.g., MP3, OGG)
    if ((Mix_Init(MIX_INIT_MP3) & MIX_INIT_MP3) != MIX_INIT_MP3) {
        std::cerr << "Warning: MP3 support not initialized! " << Mix_GetError() << "\n";
    }

    // Set volume if desired. Default volume is MIX_MAX_VOLUME (128).
    // Mix_VolumeMusic(128);

    return true;
}

void Audio::quit() {
    // Free all loaded sounds
    for (auto& pair : sound_map) {
        Mix_FreeChunk(pair.second);
    }
    sound_map.clear();

    for (auto& pair : music_map) {
        Mix_FreeMusic(pair.second);
    }
    music_map.clear();

    Mix_CloseAudio();
    Mix_Quit();
}

bool Audio::load_music(const std::string& name, const std::string& path) {
    Mix_Music* music = Mix_LoadMUS(path.c_str());
    if (!music) {
        std::cerr << "Failed to load music: " << path << " Error: " << Mix_GetError() << "\n";
        return false;
    }
    music_map[name] = music;
    return true;
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

bool Audio::load_sound(const std::string& name, const std::string& path) {
    Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
    if (!sound) {
        std::cerr << "Failed to load sound: " << path << " Error: " << Mix_GetError() << "\n";
        return false;
    }
    sound_map[name] = sound;
    return true;
}

void Audio::play_sound(const std::string& name, int loops) {
    auto it = sound_map.find(name);
    if (it != sound_map.end()) {
        Mix_PlayChannel(-1, it->second, loops);
    } else {
        std::cerr << "Sound not found: " << name << "\n";
    }
}
