#include "engine.h"
#include <iostream>

Engine::Engine() : running(false), window(nullptr), renderer(nullptr), last_time(0) {}

Engine::~Engine() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Engine::init(const std::string& title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! " << SDL_GetError() << "\n";
        return false;
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << "\n";
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << "\n";
        return false;
    }

    running = true;
    last_time = SDL_GetPerformanceCounter();
    return true;
}

void Engine::quit() {
    running = false;
}

bool Engine::is_running() const {
    return running;
}

SDL_Renderer* Engine::get_renderer() const {
    return renderer;
}

float Engine::get_delta_time() {
    Uint64 current = SDL_GetPerformanceCounter();
    float delta = (current - last_time) / (float)SDL_GetPerformanceFrequency();
    last_time = current;
    return delta;
}