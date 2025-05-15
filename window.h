#pragma once

#include <SDL2/SDL.h>
#include <unordered_map>
#include "game.h"

class Window
{
public:
    Window() : game(gridSizeX, gridSizeY) {}

    void Play();

    enum class SurfaceID
    {
        SURFACE_BLOCK_BLUE,
        SURFACE_BLOCK_RED,
        SURFACE_CAT_SIT,
        SURFACE_CAT_WALK1,
        SURFACE_CAT_WALK2,
        SURFACE_CAT_JUMP,
        SURFACE_CAT_SIT_LEFT,
        SURFACE_CAT_WALK1_LEFT,
        SURFACE_CAT_WALK2_LEFT,
        SURFACE_CAT_JUMP_LEFT,
        SURFACE_FOOD,
        SURFACE_GAME_OVER,
        SURFACE_GAME_WON
    };

private:
    void LoadAssets();
    bool HandleInputs(); // Return true unless quit event happens.
    void Render(SDL_Window *window, SDL_Surface *screenSurface);
    const int gridSizeX = 32;
    const int gridSizeY = 32;
    const int blockSize = 36;
    const int SCREEN_WIDTH = 800 * 2;
    const int SCREEN_HEIGHT = 360 * 2;
    std::unordered_map<SurfaceID, SDL_Surface *> surfaces;
    Game game;
};