#ifndef CAMERA_H
#define CAMERA_H

#include <SDL.h>

class Camera {
public:
    Camera(int screen_width, int screen_height);

    void update(const SDL_Rect& target, int world_width, int world_height);

    int get_x() const;
    int get_y() const;
    int get_width() const;
    int get_height() const;

private:
    SDL_Rect camera_rect;
    int screen_width;
    int screen_height;
};

#endif
