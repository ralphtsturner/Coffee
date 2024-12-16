#include "input.h"

void Input::update() {
    SDL_PumpEvents();
}

bool Input::is_key_pressed(SDL_Scancode scancode) const {
    return keyboard_state[scancode] != 0;
}
