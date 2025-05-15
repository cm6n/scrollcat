#pragma once

#include <SDL2/SDL.h>
#include <unordered_map>
#include "game.h"

class Window
{
public:
    Window() : game(gridSizeX, gridSizeY) {}
    bool LoadAssets();
    void Play();

    enum class SurfaceID
    {
        SURFACE_BLOCK_BLUE,
        SURFACE_BLOCK_RED,
        SURFACE_CAT_SIT,
        SURFACE_CAT_WALK1,
        SURFACE_CAT_WALK2,
        SURFACE_FOOD,
        SURFACE_GAME_OVER
    };

private:
    bool HandleInputs(); // Return true unless quit event happens.
    void Render(SDL_Window *window, SDL_Surface *screenSurface);
    const int gridSizeX = 32;
    const int gridSizeY = 32;
    const int blockSize = 36;
    std::unordered_map<SurfaceID, SDL_Surface *> surfaces;
    Game game;
};