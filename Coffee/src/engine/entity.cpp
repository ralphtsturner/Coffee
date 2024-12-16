#include "entity.h"
#include "texture.h"
#include "config.h"

Entity::Entity(float x, float y, const Animation& animation)
    : x(x), y(y), vx(0), vy(0), animation(animation), gravity_enabled(false), gravity_value(GRAVITY) {}

Entity::~Entity() {}

void Entity::update(float delta_time) {
    if (gravity_enabled) {
        vy += gravity_value * delta_time;
    }
    animation.update(delta_time);
}

void Entity::render(SDL_Renderer* renderer) {
    animation.render(renderer, (int)x, (int)y);
}

void Entity::render_with_offset(SDL_Renderer* renderer, int offset_x, int offset_y) {
    SDL_Rect collider = get_collider();
    collider.x += offset_x;
    collider.y += offset_y;
    // Use the animation’s render method, which shows the current frame
    animation.render(renderer, collider.x, collider.y);
}

void Entity::set_velocity(float vx, float vy) {
    this->vx = vx;
    this->vy = vy;
}

void Entity::get_velocity(float &out_vx, float &out_vy) const {
    out_vx = vx;
    out_vy = vy;
}

void Entity::set_position(float x, float y) {
    this->x = x;
    this->y = y;
}

void Entity::get_position(float &out_x, float &out_y) const {
    out_x = x;
    out_y = y;
}

SDL_Rect Entity::get_collider() const {
    SDL_Texture* currentTex = animation.get_current_texture();
    if (!currentTex) {
        return {(int)x, (int)y, 0, 0};
    }

    int w, h;
    SDL_QueryTexture(currentTex, NULL, NULL, &w, &h);
    return { (int)x, (int)y, w, h };
}

void Entity::set_gravity_enabled(bool enabled) {
    gravity_enabled = enabled;
}

void Entity::set_gravity_value(float value) {
    gravity_value = value;
}
