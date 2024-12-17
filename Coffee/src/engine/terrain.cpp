#include "terrain.h"
#include "config.h"
#include <iostream>
#include <cstdlib>

Terrain::Terrain(int chunk_width) : chunk_width(chunk_width) {}

void Terrain::generate_chunk(int chunk_id) {
    if (chunks.find(chunk_id) != chunks.end()) return;

    Chunk chunk;
    chunk.biome = static_cast<BiomeType>(rand() % 3);
    int start_x = chunk_id * chunk_width;

    // Generate ground tiles
    for (int i = 0; i < chunk_width / TILE_WIDTH; ++i) {
        chunk.platforms.push_back({
            start_x + i * TILE_WIDTH, // X position
            GROUND_Y,                 // Y position
            TILE_WIDTH, TILE_HEIGHT   // Width and Height
        });

        // Randomly place a tree on some tiles
        if (rand() % 5 == 0) { // 20% chance to place a tree
            chunk.trees.push_back({
                start_x + i * TILE_WIDTH + 10, // Slight offset for tree alignment
                GROUND_Y - TILE_HEIGHT,        // Place tree above the ground
                TILE_WIDTH, TILE_HEIGHT * 2    // Trees are taller
            });
        }
    }

    chunks[chunk_id] = chunk;
    std::cout << "Generated Chunk " << chunk_id << " with " << chunk.trees.size() << " trees.\n";
}

void Terrain::update_chunks(int current_chunk) {
    static int last_chunk = -1;
    if (current_chunk != last_chunk) {
        for (int i = -2; i <= 2; ++i) {
            int chunk_id = current_chunk + i;
            generate_chunk(chunk_id);
        }
        last_chunk = current_chunk;
    }
}

void Terrain::render_chunks(SDL_Renderer* renderer, SDL_Texture* grass_tex, SDL_Texture* snow_tex,
                            SDL_Texture* desert_tex, SDL_Texture* tree_tex, int camera_x, int camera_y,
                            int screen_width, int screen_height) {
    for (auto& chunk : chunks) {
        SDL_Texture* current_texture = grass_tex;
        if (chunk.second.biome == SNOWY) current_texture = snow_tex;
        else if (chunk.second.biome == DESERT) current_texture = desert_tex;

        // Render ground platforms
        for (auto& platform : chunk.second.platforms) {
            if (platform.x + platform.w >= camera_x && platform.x <= camera_x + screen_width &&
                platform.y + platform.h >= camera_y && platform.y <= camera_y + screen_height) {
                SDL_Rect dest = { platform.x - camera_x, platform.y - camera_y, platform.w, platform.h };
                SDL_RenderCopy(renderer, current_texture, nullptr, &dest);
            }
        }

        // Render trees
        for (auto& tree : chunk.second.trees) {
            if (tree.x + tree.w >= camera_x && tree.x <= camera_x + screen_width &&
                tree.y + tree.h >= camera_y && tree.y <= camera_y + screen_height) {
                SDL_Rect dest = { tree.x - camera_x, tree.y - camera_y, tree.w, tree.h };
                SDL_RenderCopy(renderer, tree_tex, nullptr, &dest);
            }
        }
    }
}

std::map<int, Chunk>& Terrain::get_chunks() {
    return chunks;
}