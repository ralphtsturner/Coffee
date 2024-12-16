#ifndef AUDIO_H
#define AUDIO_H

#include <string>
#include <map>
#include <vector>
#include <SDL_mixer.h>

class Audio {
public:
    static bool init();
    static void quit();

    static void load_music(const std::string& name, const std::string& path);
    static void play_music(const std::string& name, int loops = -1);
    static void pause_music();
    static void resume_music();
    static void stop_music();

    static void load_sound(const std::string& name, const std::string& path);
    static void play_sound(const std::string& name, int loops = 0);

    static void set_music_sequence(const std::vector<std::string>& sequence);
    static void set_music_sequence(std::initializer_list<std::string> sequence);

private:
    static void play_next_track();

    static std::map<std::string, Mix_Chunk*> sound_map;
    static std::map<std::string, Mix_Music*> music_map;
    static std::vector<std::string> music_sequence;
    static size_t current_track;
};

#endif
