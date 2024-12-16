#ifndef CONFIG_H
#define CONFIG_H

static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 600;
static const char* WINDOW_TITLE = "Gravity Demo";

// Movement and physics
static const float SPEED = 200.0f;        // Horizontal movement speed
static const float GRAVITY = 1000.0f;     // Gravity acceleration (px/s^2)

// Asset paths
static const char* PLAYER_FRAME_1 = "res/characters/farmer1.png";
static const char* PLAYER_FRAME_2 = "res/characters/farmer2.png";
static const char* GRASS_TEXTURE = "res/ground/grass.png";

#endif
