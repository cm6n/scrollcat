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
    surfaces[SurfaceID::SURFACE_BLOCK_BLUE] = loadBMPOrThrow("assets/block_blue_36x36.bmp");
    surfaces[SurfaceID::SURFACE_BLOCK_RED] = loadBMPOrThrow("assets/block_red_12x12.bmp");
    surfaces[SurfaceID::SURFACE_CAT_SIT] = loadBMPOrThrow("assets/cat_sit_36x36.bmp");
    surfaces[SurfaceID::SURFACE_CAT_WALK1] = loadBMPOrThrow("assets/cat_walk1_36x36.bmp");
    // TODO: load different cat walk 2.
    surfaces[SurfaceID::SURFACE_CAT_WALK2] = loadBMPOrThrow("assets/cat_walk1_36x36.bmp");
    // TODO: Add a food image.
    surfaces[SurfaceID::SURFACE_FOOD] = loadBMPOrThrow("assets/block_green_12x12.bmp");
    // TODO: Add a game over image.
    surfaces[SurfaceID::SURFACE_GAME_OVER] = loadBMPOrThrow("assets/block_red_12x12.bmp");
    return true;
}

static void drawSurface(SDL_Surface *surface, SDL_Surface *screenSurface, int x, int y)
{
    SDL_Rect destinationRect;
    destinationRect.x = x;  // Offset from the left edge
    destinationRect.y = y; // Offset from the top edge
    SDL_BlitSurface(surface, NULL, screenSurface, &destinationRect);
}

void Window::Render(SDL_Window *window, SDL_Surface *screenSurface)
{
    // Fill the surface with white
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 255, 255, 255));

    // Render blocks
    for (const auto &block : game.GetBlocks())
    {
        int x = block.first * blockSize;
        int y = block.second * blockSize;
        drawSurface(surfaces[SurfaceID::SURFACE_BLOCK_BLUE], screenSurface, x, y);
    }
    // Render food
    for (const auto &food : game.GetFood())
    {
        int x = food.first * blockSize;
        int y = food.second * blockSize;
        drawSurface(surfaces[SurfaceID::SURFACE_FOOD], screenSurface, x, y);
    }
    // Render cat
    int catX = game.GetCatX() * blockSize;
    int catY = game.GetCatY() * blockSize;
    auto [catXvelocity, catYvelocity] = game.GetCatVelocity();
    if (catXvelocity == 0 && catYvelocity == 0)
    {
        drawSurface(surfaces[SurfaceID::SURFACE_CAT_SIT], screenSurface, catX, catY);
    }
    else if (catXvelocity != 0 || catYvelocity != 0)
    {
        static int catWalk = 0;
        catWalk++;
        if (catWalk) {
            drawSurface(surfaces[SurfaceID::SURFACE_CAT_WALK1], screenSurface, catX, catY);
            catWalk = 0;
        } else {
            drawSurface(surfaces[SurfaceID::SURFACE_CAT_WALK2], screenSurface, catX, catY);
        }
    }

    // Render end of game
    auto [endOfGameX, endOfGameY] = game.GetEndOfGame();
    drawSurface(surfaces[SurfaceID::SURFACE_BLOCK_RED], screenSurface, endOfGameX*blockSize, endOfGameY*blockSize);

    // Render game over
    if (game.GameOver())
    {
        int gameOverX = 0; // Centered on the screen
        int gameOverY = 0; // Centered on the screen
        drawSurface(surfaces[SurfaceID::SURFACE_GAME_OVER], screenSurface, gameOverX, gameOverY);
    }
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

    const int SCREEN_WIDTH = 640*2;
    const int SCREEN_HEIGHT = 480*2;
    SDL_Window *window = NULL; // The window we'll be rendering to.
    SDL_Surface *screenSurface = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        throw std::runtime_error("SDL_Init Error: " + std::string(SDL_GetError()));
    }
    window = SDL_CreateWindow("ScrollCat", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
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