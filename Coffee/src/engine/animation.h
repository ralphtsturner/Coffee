#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL.h>
#include <vector>

class Animation {
public:
    Animation(float frame_time = 0.1f, bool loop = true);

    void add_frame(SDL_Texture* frame_texture);
    void play();
    void pause();
    void reset();
    void update(float delta_time);
    void render(SDL_Renderer* renderer, int x, int y) const;
    void set_loop(bool loop);
    void set_frame_time(float frame_time);
    bool is_playing() const;
    SDL_Texture* get_current_texture() const;

private:
    std::vector<SDL_Texture*> frames;
    float frame_time;
    float timer;
    size_t current_frame;
    bool playing;
    bool loop_anim;
};

#endif
