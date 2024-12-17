#include "camera.h"

Camera::Camera(int screen_width, int screen_height)
    : screen_width(screen_width), screen_height(screen_height) {
    camera_rect = {0, 0, screen_width, screen_height};
}

void Camera::update(const SDL_Rect& target, int world_width, int world_height) {
    camera_rect.x = target.x + (target.w / 2) - (screen_width / 2);
    camera_rect.y = target.y + (target.h / 2) - (screen_height / 2);

    // Clamp the camera to prevent showing empty space
    if (camera_rect.x < 0) camera_rect.x = 0;
    if (camera_rect.y < 0) camera_rect.y = 0;
}

int Camera::get_x() const { return camera_rect.x; }
int Camera::get_y() const { return camera_rect.y; }