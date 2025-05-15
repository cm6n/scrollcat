#include "game.h"
#include <fstream>
#include <string>
#include <iostream>

void Game::InitGame()
{
    // Initialize the game state
    catX = 0;
    catY = 0;
    food.clear();
    blocks.clear();
    gameOver = false;
    currentDirection = Direction::NONE;
    
    // Read level0.txt and populate food and blocks.
    // Each line in the file represents a column in the grid.
    // "|" represents a block
    // "F" represents food
    // "C" represents the initial cat position. 
    // "E" represents the end of the level.

    // Read levels/level0.txt line by line:
    std::ifstream levelFile("levels/level0.txt");
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
                std::cout << "Block at: (" << x << ", " << y << ")" << std::endl;
            } else if (c == 'F') {
                // Food
                food.push_back(std::make_pair(x, y));
                std::cout << "Food at: (" << x << ", " << y << ")" << std::endl;
            } else if (c == 'C') {
                // Cat initial position
                catX = x;
                catY = y;
                std::cout << "Cat initial position at: (" << catX << ", " << catY << ")" << std::endl;
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
    // Physics updates.

    // User input updates.
    // Update the cat's position based on the current direction.
    // Move unless blocked by a box.
    int newCatX = catX;
    int newCatY = catY;
    switch (currentDirection)
    {
        case Direction::UP:
            std::cout << "UP" << std::endl;
            catYvelocity -= 3;
            break;
        case Direction::DOWN:
            std::cout << "DOWN" << std::endl;
            catYvelocity += 3;
            break;
        case Direction::LEFT:
            std::cout << "LEFT" << std::endl;
            catXvelocity -= 3;
            break;
        case Direction::RIGHT:
            std::cout << "RIGHT" << std::endl;
            catXvelocity += 3;
            break;
    }
    std::cout << "catXvelocity: " << catXvelocity << " ";
    std::cout << "catYvelocity: " << catYvelocity << std::endl;
    int tempXvelocity = catXvelocity;
    int tempYvelocity = catYvelocity;
    while (tempXvelocity != 0 || tempYvelocity != 0)
    {
        int tempCatX = newCatX;
        int tempCatY = newCatY;
        if (tempXvelocity > 0)
        {
            tempCatX = newCatX;
            newCatX++;
            tempXvelocity--;
        }
        else if (tempXvelocity < 0)
        {
            tempCatX = newCatX;
            newCatX--;
            tempXvelocity++;
        }
        if (tempYvelocity > 0)
        {
            tempCatY = newCatY;
            newCatY++;
            tempYvelocity--;
        }
        else if (tempYvelocity < 0)
        {
            tempCatY = newCatY;
            newCatY--;
            tempYvelocity++;
        }
        // Check for collisions with blocks
        for (const auto &block : blocks)
        {
            if (block.first == newCatX && block.second == newCatY)
            {
                newCatX = tempCatX;
                newCatY = tempCatY;
                break; // Stop checking other blocks
            }
        }
    }

    // Slow down the cat
    if (catXvelocity > 0)
    {
        catXvelocity--;
    }
    else if (catXvelocity < 0)
    {
        catXvelocity++;
    }
    if (catYvelocity > 0)
    {
        catYvelocity--;
    }
    else if (catYvelocity < 0)
    {
        catYvelocity++;
    }

    // Apply gravity
    if (catYvelocity < 1) // Cat is rising.
    {
        catYvelocity++;
    }

    currentDirection = Direction::NONE;

    catX = newCatX;
    catY = newCatY;
}

void Game::ChangeDirection(Direction newDirection) 
{
    currentDirection = newDirection;
}

bool Game::GameOver()
{
    return gameOver;
}
