#include "physics.h"
#include "collision.h"
#include <algorithm>

void PhysicsSystem::apply_gravity(Entity& entity, float delta_time, float gravity) {
    float vx, vy;
    entity.get_velocity(vx, vy);
    vy += gravity * delta_time;
    std::cout << "Gravity Applied: " << vy << "\n"; // Debug print
    entity.set_velocity(vx, vy);
}

bool PhysicsSystem::is_on_ground(const Entity& entity, const std::vector<SDL_Rect>& platforms) {
    SDL_Rect collider = entity.get_collider();
    collider.y += 2; // Tolerance for small positional offsets
    for (auto& p : platforms) {
        if (Collision::AABB(collider, p)) {
            std::cout << "On Ground: " << collider.y << "\n"; // Debug print
            return true;
        }
    }
    return false;
}

void PhysicsSystem::jump(Entity& entity, float jump_strength) {
    float vx, vy;
    entity.get_velocity(vx, vy);
    // Set upward velocity
    vy = jump_strength;
    entity.set_velocity(vx, vy);
}

void PhysicsSystem::apply_friction(Entity& entity, float friction, float delta_time) {
    float vx, vy;
    entity.get_velocity(vx, vy);
    // Apply friction only if vx is not zero
    if (vx > 0) {
        vx = std::max(0.0f, vx - friction * delta_time);
    } else if (vx < 0) {
        vx = std::min(0.0f, vx + friction * delta_time);
    }
    entity.set_velocity(vx, vy);
}