# Coffee
A better, refactored, Iris Engine Model

 Coffee is a simple 2D game engine built on top of **SDL2** (a refactored and better version of Iris Engine which is now discontinued) providing a foundation for game development with features like:

- Window and renderer management
- Input handling (keyboard)
- Texture loading and rendering
- Basic entity management and animations
- Collision detection and simple physics (gravity)
- Audio playback (music and sound effects)
- A simple example scene with platforms and player movement/jumping
- Biome & Terrain generation.

## Features

- **Rendering:** Load textures and render them on a window with SDL2.
- **Input Handling:** Detect keyboard input for movement and jumping.
- **Entity & Animation:** Create entities that can have animations (either via spritesheet or individual frames).
- **Collision & Physics:** Check collisions against platforms and apply gravity and simple jump physics.
- **Audio:** Play background music and sound effects using SDL2_mixer.
- ***Terrain & Biome:*** Vary the game with different biomes and infinite terrain generation.

  
## Getting Started

### Prerequisites

- **SDL2**, **SDL2_image**, and **SDL2_mixer** must be installed on your system.
  - On macOS (with Homebrew):  
    ```bash
    brew install sdl2 sdl2_image sdl2_mixer
    ```
  - On Ubuntu/Debian:  
    ```bash
    sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev
    ```
    - On Windows/10-11
    ```
    Download Visual Studio and the SDL2 dependencies from their github. Link them to Visual Studio and then compile.
    ```
    
- A C++17 compatible compiler (e.g., `g++` or `clang++`).

### Building the Project

Use the provided `Makefile`:

```bash
make
