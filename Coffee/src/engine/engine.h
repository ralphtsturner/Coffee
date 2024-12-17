#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include <string>

class Engine {
public:
    Engine();
    ~Engine();

    bool init(const std::string& title, int width, int height);
    void quit();
    bool is_running() const;
    SDL_Renderer* get_renderer() const;
    float get_delta_time();

private:
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Uint64 last_time;
};

#endif