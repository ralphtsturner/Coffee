#ifndef PHYSICS_H
#define PHYSICS_H

#include <SDL.h>
#include <vector>
#include "entity.h"

class PhysicsSystem {
public:
    static void apply_gravity(Entity& entity, float delta_time, float gravity);
    static bool is_on_ground(const Entity& entity, const std::vector<SDL_Rect>& platforms);
    static void jump(Entity& entity, float jump_strength);
    static void apply_friction(Entity& entity, float friction, float delta_time);
};

#endif