#include "game.h"

void Game::InitGame()
{
}

void Game::Update()
{
}

void Game::ChangeDirection(Direction newDirection) 
{
    currentDirection = newDirection;
}

bool Game::GameOver()
{
    return gameOver;
}
