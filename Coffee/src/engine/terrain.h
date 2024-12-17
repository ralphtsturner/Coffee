#ifndef TERRAIN_H
#define TERRAIN_H

#include <SDL.h>
#include <vector>
#include <map>

enum BiomeType {
    GRASSLAND,
    SNOWY,
    DESERT
};

struct Chunk {
    std::vector<SDL_Rect> platforms; // Ground platforms
    std::vector<SDL_Rect> trees;     // Tree positions
    BiomeType biome;
};

class Terrain {
public:
    Terrain(int chunk_width);

    void generate_chunk(int chunk_id);
    void update_chunks(int current_chunk);
    void render_chunks(SDL_Renderer* renderer, SDL_Texture* grass_tex, SDL_Texture* snow_tex,
                   SDL_Texture* desert_tex, SDL_Texture* tree_tex, int camera_x, int camera_y,
                   int screen_width, int screen_height);
    std::map<int, Chunk>& get_chunks();

private:
    std::map<int, Chunk> chunks;
    int chunk_width;
};

#endif