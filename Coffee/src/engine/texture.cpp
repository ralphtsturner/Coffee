#include "texture.h"
#include <SDL_image.h>
#include <iostream>

SDL_Texture* Texture::load_texture(const std::string& path, SDL_Renderer* renderer) {
    SDL_Texture* tex = IMG_LoadTexture(renderer, path.c_str());
    if (!tex) {
        std::cerr << "Failed to load texture " << path << ": " << IMG_GetError() << "\n";
    }
    return tex;
}

void Texture::render(SDL_Texture* texture, int x, int y, SDL_Renderer* renderer) {
    if (!texture) return;
    SDL_Rect dest;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    dest.x = x;
    dest.y = y;
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}
