#ifndef CONFIG_H
#define CONFIG_H

// Window settings
static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 600;
static const char* WINDOW_TITLE = "Coffee Engine";

// World bounds (for camera clamping)
static const int WORLD_WIDTH = 2000;
static const int WORLD_HEIGHT = 1200;

// Physics & Movement
static const float GRAVITY = 1000.0f; // Gravity acceleration (px/s^2)
static const float SPEED = 250.0f;    // Horizontal speed
static const float JUMP_STRENGTH = -500.0f;

// Asset paths
static const char* PLAYER_FRAME_1 = "res/characters/farmer1.png";
static const char* PLAYER_FRAME_2 = "res/characters/farmer2.png";
static const char* GRASS_TEXTURE = "res/ground/grass.png";

#endif
