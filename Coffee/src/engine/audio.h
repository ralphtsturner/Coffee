#ifndef AUDIO_H
#define AUDIO_H

#include <SDL_mixer.h>
#include <string>
#include <map>

class Audio {
public:
    static bool init();
    static void quit();

    static void load_music(const std::string& name, const std::string& path);
    static void play_music(const std::string& name, int loops = -1);
    static void stop_music();

private:
    static std::map<std::string, Mix_Music*> music_map;
};

#endif