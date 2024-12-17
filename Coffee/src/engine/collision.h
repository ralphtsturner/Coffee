#ifndef COLLISION_H
#define COLLISION_H

#include <SDL.h>

class Collision {
public:
    static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
};

#endif