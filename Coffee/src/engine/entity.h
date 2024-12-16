#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>
#include "animation.h"

class Entity {
public:
    Entity(float x, float y, const Animation& animation);
    ~Entity();

    void update(float delta_time);
    void render(SDL_Renderer* renderer);

    void render_with_offset(SDL_Renderer* renderer, int offset_x, int offset_y); // Add this line

    void set_velocity(float vx, float vy);
    void get_velocity(float &out_vx, float &out_vy) const;

    void set_position(float x, float y);
    void get_position(float &out_x, float &out_y) const;

    SDL_Rect get_collider() const;

    void set_gravity_enabled(bool enabled);
    void set_gravity_value(float value);

private:
    float x, y;
    float vx, vy;
    Animation animation;

    bool gravity_enabled;
    float gravity_value;
};

#endif
