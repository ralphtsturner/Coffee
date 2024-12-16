#include "engine/engine.h"
#include "engine/input.h"
#include "engine/texture.h"
#include "engine/config.h"
#include "engine/entity.h"
#include "engine/collision.h"
#include "engine/animation.h"
#include "engine/audio.h"
#include "engine/camera.h"
#include <SDL.h>
#include <iostream>
#include <vector>

int main() {
    Engine engine;
    if (!engine.init(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT)) {
        return -1;
    }

    if (!Audio::init()) {
        std::cerr << "Audio failed to initialize.\n";
        return -1;
    }

    // Load music tracks
    Audio::load_music("bg1", "res/music/background.mp3");
    Audio::load_music("bg2", "res/music/background-2.mp3");
    Audio::set_music_sequence({ "bg1", "bg2" });

    Input input;

    // Load player frames
    SDL_Texture* frame1 = Texture::load_texture(PLAYER_FRAME_1, engine.get_renderer());
    SDL_Texture* frame2 = Texture::load_texture(PLAYER_FRAME_2, engine.get_renderer());

    // Create player animation
    Animation playerAnim(0.2f, true);
    playerAnim.add_frame(frame1);
    playerAnim.add_frame(frame2);

    // Create player entity
    Entity player(100.0f, 100.0f, playerAnim);
    player.set_gravity_enabled(true);
    player.set_gravity_value(GRAVITY);

    // Load grass texture
    SDL_Texture* grass_tex = Texture::load_texture(GRASS_TEXTURE, engine.get_renderer());

    // Create platforms
    std::vector<SDL_Rect> collidable_objects;

    int tile_width = 64;
    int tile_height = 64;

    // Ground row at y=550
    for (int i = 0; i < 13; ++i) {
        SDL_Rect grass_rect = { i * tile_width, 550, tile_width, tile_height };
        collidable_objects.push_back(grass_rect);
    }

    // Second platform row at y=400
    for (int i = 3; i < 8; ++i) {
        SDL_Rect grass_rect = { i * tile_width, 400, tile_width, tile_height };
        collidable_objects.push_back(grass_rect);
    }

    // Higher single platform at y=300
    {
        SDL_Rect grass_rect = { 6 * tile_width, 300, tile_width, tile_height };
        collidable_objects.push_back(grass_rect);
    }

    // Another platform row at y=450
    for (int i = 10; i < 12; ++i) {
        SDL_Rect grass_rect = { i * tile_width, 450, tile_width, tile_height };
        collidable_objects.push_back(grass_rect);
    }

    // Create camera
    Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT);

    while (engine.is_running()) {
        float dt = engine.get_delta_time();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                engine.quit();
            }
        }

        input.update();
        if (input.is_key_pressed(SDL_SCANCODE_ESCAPE)) {
            engine.quit();
        }

        // Update entity velocities (gravity, animation frames)
        player.update(dt);

        // Get player position and velocity
        float px, py;
        player.get_position(px, py);

        float vx, vy;
        player.get_velocity(vx, vy);

        // Horizontal input
        vx = 0.0f;
        if (input.is_key_pressed(SDL_SCANCODE_A)) vx = -SPEED;
        if (input.is_key_pressed(SDL_SCANCODE_D)) vx = SPEED;

        // Check if on platform to allow jumping
        bool on_platform = false;
        {
            SDL_Rect feetRect = player.get_collider();
            feetRect.y += 1;
            for (auto& obj : collidable_objects) {
                if (Collision::AABB(feetRect, obj)) {
                    on_platform = true;
                    break;
                }
            }
        }

        // Jump if on platform
        if (input.is_key_pressed(SDL_SCANCODE_SPACE) && on_platform) {
            vy = JUMP_STRENGTH;
        }

        player.set_velocity(vx, vy);

        // Move horizontally first
        px += vx * dt;
        player.set_position(px, py);

        // Horizontal collision check
        {
            SDL_Rect playerRect = player.get_collider();
            for (auto& obj : collidable_objects) {
                if (Collision::AABB(playerRect, obj)) {
                    // Collided horizontally
                    if (vx > 0) {
                        player.set_position(obj.x - playerRect.w, py);
                    } else if (vx < 0) {
                        player.set_position(obj.x + obj.w, py);
                    }
                    // Stop horizontal movement
                    player.set_velocity(0.0f, vy);
                    break;
                }
            }
        }

        // After horizontal resolved, move vertically
        player.get_position(px, py);
        player.get_velocity(vx, vy);

        py += vy * dt;
        player.set_position(px, py);

        // Vertical collision check
        {
            SDL_Rect playerRect = player.get_collider();
            for (auto& obj : collidable_objects) {
                if (Collision::AABB(playerRect, obj)) {
                    // Collided vertically
                    if (vy > 0) {
                        player.set_position(px, obj.y - playerRect.h);
                    } else if (vy < 0) {
                        player.set_position(px, obj.y + obj.h);
                    }
                    // Stop vertical movement
                    player.set_velocity(vx, 0.0f);
                    break;
                }
            }
        }

        // Update camera to follow player
        SDL_Rect playerRect = player.get_collider();
        camera.update(playerRect, WORLD_WIDTH, WORLD_HEIGHT);

        // Render
        SDL_Renderer* renderer = engine.get_renderer();
        SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
        SDL_RenderClear(renderer);

        // Render platforms with camera offset
        for (const auto& object : collidable_objects) {
            Texture::render(grass_tex, object.x - camera.get_x(), object.y - camera.get_y(), renderer);
        }

        player.render_with_offset(renderer, -camera.get_x(), -camera.get_y());

        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyTexture(frame1);
    SDL_DestroyTexture(frame2);
    SDL_DestroyTexture(grass_tex);
    Audio::quit();
    engine.quit();
    return 0;
}
