#include "animation.h"
#include <iostream>

Animation::Animation(float frame_time, bool loop)
    : frame_time(frame_time), timer(0.0f), current_frame(0), playing(true), loop_anim(loop) {}

void Animation::add_frame(SDL_Texture* frame_texture) {
    if (frame_texture) {
        frames.push_back(frame_texture);
    } else {
        std::cerr << "Warning: Null frame added to animation.\n";
    }
}

void Animation::play() {
    playing = true;
}

void Animation::pause() {
    playing = false;
}

void Animation::reset() {
    current_frame = 0;
    timer = 0.0f;
}

void Animation::update(float delta_time) {
    if (!playing || frames.empty()) return;

    timer += delta_time;
    if (timer >= frame_time) {
        timer -= frame_time;
        current_frame++;
        if (current_frame >= frames.size()) {
            if (loop_anim) {
                current_frame = 0;
            } else {
                current_frame = frames.size() - 1;
                pause();
            }
        }
    }
}

void Animation::render(SDL_Renderer* renderer, int x, int y) const {
    if (frames.empty()) return;

    SDL_Texture* tex = frames[current_frame];
    int w, h;
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    SDL_Rect dest = {x, y, w, h};
    SDL_RenderCopy(renderer, tex, NULL, &dest);
}

void Animation::set_loop(bool loop) {
    loop_anim = loop;
}

void Animation::set_frame_time(float frame_time) {
    this->frame_time = frame_time;
}

bool Animation::is_playing() const {
    return playing;
}

SDL_Texture* Animation::get_current_texture() const {
    if (frames.empty()) return nullptr;
    return frames[current_frame];
}