#ifndef CONFIG_H
#define CONFIG_H

// Window settings
static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 600;
static const char* WINDOW_TITLE = "Infinite Terrain Demo";

// World settings
static const int WORLD_HEIGHT = 1200;
static const int GROUND_Y = 1136;       // Fixed Y position for the ground
static const int TILE_WIDTH = 64;       // Width of each tile
static const int TILE_HEIGHT = 64;      // Height of each tile

// Physics and movement
static const float GRAVITY = 800.0f;
static const float SPEED = 250.0f;
static const float JUMP_STRENGTH = -400.0f;

// Texture paths
static const char* GRASS_TEXTURE = "res/ground/grass.png";
static const char* SNOW_TEXTURE = "res/ground/snow.png";
static const char* DESERT_TEXTURE = "res/ground/desert.png";
static const char* PLAYER_FRAME_1 = "res/characters/farmer1.png";
static const char* PLAYER_FRAME_2 = "res/characters/farmer2.png";
static const char* TREE_TEXTURE_1 = "res/objects/tree1.png";
static const char* TREE_TEXTURE_2 = "res/objects/tree2.png";

#endif