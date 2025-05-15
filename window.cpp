#include "window.h"
#include <stdexcept>

static SDL_Surface *loadBMPOrThrow(const char *filename)
{
    SDL_Surface *surface = SDL_LoadBMP(filename);
    if (surface == NULL)
    {
        throw std::runtime_error("Unable to load image " + std::string(filename) + "! SDL Error: " + std::string(SDL_GetError()));
    }
    return surface;
}

bool Window::LoadAssets()
{
    surfaces[SurfaceID::SURFACE_BLOCK_BLUE] = loadBMPOrThrow("assets/block_blue_12x12.bmp");
    surfaces[SurfaceID::SURFACE_BLOCK_RED] = loadBMPOrThrow("assets/block_red_12x12.bmp");
    return true;
}

void Window::Play()
{
    LoadAssets();
}