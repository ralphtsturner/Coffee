#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

class Input {
public:
    void update();
    bool is_key_pressed(SDL_Scancode scancode) const;

private:
    const Uint8* keyboard_state = SDL_GetKeyboardState(nullptr);
};

#endif