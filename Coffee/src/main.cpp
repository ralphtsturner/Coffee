#include "engine.h"
#include "input.h"
#include "entity.h"
#include "animation.h"
#include "camera.h"
#include "collision.h"
#include "texture.h"
#include "terrain.h"
#include "config.h"

#include <iostream>

int main() {
    Engine engine;
    if (!engine.init(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT)) return -1;

    SDL_Renderer* renderer = engine.get_renderer();
    SDL_Texture* grass_tex = Texture::load_texture(GRASS_TEXTURE, renderer);
    SDL_Texture* snow_tex = Texture::load_texture(SNOW_TEXTURE, renderer);
    SDL_Texture* desert_tex = Texture::load_texture(DESERT_TEXTURE, renderer);
    SDL_Texture* tree_tex = Texture::load_texture(TREE_TEXTURE_1, renderer); // Load one tree texture


    Animation playerAnim(0.2f, true);
    playerAnim.add_frame(Texture::load_texture(PLAYER_FRAME_1, renderer));
    playerAnim.add_frame(Texture::load_texture(PLAYER_FRAME_2, renderer));

    Entity player(100, GROUND_Y - TILE_HEIGHT, playerAnim);
    Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT);
    Input input;

    Terrain terrain(800); // Chunk width
    terrain.update_chunks(0); // Generate initial chunks

    float vx = 0.0f, vy = 0.0f;
    bool on_ground = false;

    while (engine.is_running()) {
        float dt = engine.get_delta_time();
        input.update();

        if (input.is_key_pressed(SDL_SCANCODE_ESCAPE)) engine.quit();

        // Movement
        vx = 0;
        if (input.is_key_pressed(SDL_SCANCODE_A)) vx = -SPEED;
        if (input.is_key_pressed(SDL_SCANCODE_D)) vx = SPEED;

        // Gravity and jumping
        on_ground = false;
        vy += GRAVITY * dt;

        // Apply position updates
        float px, py;
        player.get_position(px, py);
        px += vx * dt;
        py += vy * dt;
        player.set_position(px, py);

        // Update terrain
        int current_chunk = px / 800;
        terrain.update_chunks(current_chunk);

        // Collision detection with all active chunks
        SDL_Rect playerRect = player.get_collider();
        for (auto& chunk : terrain.get_chunks()) {
            for (auto& platform : chunk.second.platforms) {
                if (Collision::AABB(playerRect, platform)) {
                    if (vy > 0) py = platform.y - playerRect.h; // Align to top of platform
                    if (vy < 0) py = platform.y + platform.h;   // Align to bottom
                    vy = 0;
                    on_ground = true;
                    player.set_position(px, py);
                }
            }
        }

        if (on_ground && input.is_key_pressed(SDL_SCANCODE_SPACE)) {
            vy = JUMP_STRENGTH; // Jump
        }

        player.set_velocity(vx, vy);
        player.update(dt); // Update animation

        // Update camera
        camera.update(player.get_collider(), 0, WORLD_HEIGHT);

        // Rendering
        SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
        SDL_RenderClear(renderer);

        // Rendering
        terrain.render_chunks(renderer, grass_tex, snow_tex, desert_tex,
                      tree_tex, camera.get_x(), camera.get_y(), WINDOW_WIDTH, WINDOW_HEIGHT);
        player.render_with_offset(renderer, -camera.get_x(), -camera.get_y());

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(grass_tex);
    SDL_DestroyTexture(snow_tex);
    SDL_DestroyTexture(desert_tex);
    engine.quit();

    return 0;
}