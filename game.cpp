#include "game.h"
#include <fstream>
#include <string>

void Game::InitGame()
{
    // Initialize the game state
    catX = 0;
    catY = 0;
    food.clear();
    blocks.clear();
    gameOver = false;
    currentDirection = Direction::RIGHT;
    
    // Read level0.txt and populate food and blocks.
    // Each line in the file represents a column in the grid.
    // "|" represents a block
    // "F" represents food
    // "C" represents the initial cat position. 
    // "E" represents the end of the level.

    // Read levels/level0.txt line by line:
    std::ifstream levelFile("scrollcat/levels/level0.txt");
    if (!levelFile.is_open()) {
        // Failed to open the file
        gameOver = true;
        return;
    }

    std::string line;
    int x = 0; // Column index
    
    while (std::getline(levelFile, line)) {
        for (int y = 0; y < line.length(); y++) {
            char c = line[y];
            
            if (c == '|') {
                // Block
                blocks.push_back(std::make_pair(x, y));
            } else if (c == 'F') {
                // Food
                food.push_back(std::make_pair(x, y));
            } else if (c == 'C') {
                // Cat initial position
                catX = x;
                catY = y;
            } else if (c == 'E') {
                // End of level marker
                // Could be used for level completion logic
            }
        }
        x++; // Move to the next column
    }
    
    levelFile.close();
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
