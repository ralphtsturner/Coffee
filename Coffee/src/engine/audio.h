#ifndef AUDIO_H
#define AUDIO_H

#include <string>
#include <map>
#include <SDL_mixer.h>

class Audio {
public:
    // Initialize and shutdown the audio system
    static bool init(int frequency = 44100, Uint16 format = MIX_DEFAULT_FORMAT, int channels = 2, int chunksize = 2048);
    static void quit();

    // Music methods
    static bool load_music(const std::string& name, const std::string& path);
    static void play_music(const std::string& name, int loops = -1); // -1 means loop indefinitely
    static void pause_music();
    static void resume_music();
    static void stop_music();

    // Sound effects
    static bool load_sound(const std::string& name, const std::string& path);
    static void play_sound(const std::string& name, int loops = 0); // 0 means play once

private:
    static std::map<std::string, Mix_Music*> music_map;
    static std::map<std::string, Mix_Chunk*> sound_map;
};

#endif
