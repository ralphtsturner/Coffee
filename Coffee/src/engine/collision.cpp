#include "collision.h"
#include <SDL.h>

bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB) {
    return SDL_HasIntersection(&rectA, &rectB);
}
