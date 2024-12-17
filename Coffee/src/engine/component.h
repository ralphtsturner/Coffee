#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL.h>

class Component {
public:
    virtual ~Component() = default;
    virtual void update(float delta_time) {}
    virtual void render(SDL_Renderer* renderer) {}
};

#endif