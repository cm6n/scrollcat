#include "window.h"

#include <stdexcept>

#include "game.h"

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
    // TODO: Add a cat image.
    surfaces[SurfaceID::SURFACE_CAT] = loadBMPOrThrow("assets/block_blue_12x12.bmp");
    // TODO: Add a food image.
    surfaces[SurfaceID::SURFACE_FOOD] = loadBMPOrThrow("assets/block_blue_12x12.bmp");
    // TODO: Add a game over image.
    surfaces[SurfaceID::SURFACE_GAME_OVER] = loadBMPOrThrow("assets/block_blue_12x12.bmp");
    return true;
}

void Window::Render(SDL_Window *window, SDL_Surface *screenSurface)
{
    // Fill the surface with white
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 255, 255, 255));

    SDL_Rect destinationRect;
    destinationRect.x = 100;  // Offset from the left edge
    destinationRect.y = 100; // Offset from the top edge
    SDL_BlitSurface(surfaces[SurfaceID::SURFACE_BLOCK_BLUE], NULL, screenSurface, &destinationRect);

    // Update the surface
    SDL_UpdateWindowSurface(window);
}

bool Window::HandleInputs()
{
    SDL_Event e;
    while (SDL_PollEvent(&e)) // Process all events
    {
        if (e.type == SDL_QUIT)
        {
            return false;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_UP:
                game.ChangeDirection(Game::Direction::UP);
                break;
            case SDLK_DOWN:
                game.ChangeDirection(Game::Direction::DOWN);
                break;
            case SDLK_LEFT:
                game.ChangeDirection(Game::Direction::LEFT);
                break;
            case SDLK_RIGHT:
                game.ChangeDirection(Game::Direction::RIGHT);
                break;
            case SDLK_RETURN:
                if (game.GameOver())
                {
                    game.InitGame();
                }
            }
        }
    }
    return true;
}

void Window::Play()
{
    LoadAssets();

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    SDL_Window *window = NULL; // The window we'll be rendering to.
    SDL_Surface *screenSurface = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        throw std::runtime_error("SDL_Init Error: " + std::string(SDL_GetError()));
    }
    window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        throw std::runtime_error("Window could not be created! SDL_Error: " + std::string(SDL_GetError()));
    }
    screenSurface = SDL_GetWindowSurface(window);
    if (screenSurface == NULL)
    {
        throw std::runtime_error("Window surface could not be created! SDL_Error: " + std::string(SDL_GetError()));
    }
    // Run the game
    game.InitGame();
    bool keepRunning = true;
    while (keepRunning)
    {
        SDL_Delay(100); // Small delay.
        keepRunning = HandleInputs();
        game.Update();
        Render(window, screenSurface);
    }
    // Cleanup
    for (auto &surface : surfaces)
    {
        SDL_FreeSurface(surface.second);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}