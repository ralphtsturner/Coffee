#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <string>

class Texture {
public:
    static SDL_Texture* load_texture(const std::string& path, SDL_Renderer* renderer);
    static void render(SDL_Texture* texture, int x, int y, SDL_Renderer* renderer);
};

#endif