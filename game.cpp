#include "game.h"
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

void Game::InitGame()
{
    // Initialize the game state
    catX = 0;
    catY = 0;
    catXvelocity = 0;
    catYvelocity = 0;
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
    if (level > maxLevel)
    {
        throw std::runtime_error("Level out of range.");
    }
    std::ifstream levelFile("levels/level" + std::to_string(level) + ".txt");
    if (!levelFile.is_open())
    {
        // Failed to open the file
        gameOver = true;
        return;
    }

    std::string line;
    int x = 0; // Column index

    while (std::getline(levelFile, line))
    {
        for (int y = 0; y < line.length(); y++)
        {
            char c = line[y];

            if (c == '|')
            {
                // Block
                blocks.push_back(std::make_pair(x, y));
            }
            else if (c == 'F')
            {
                // Food
                food.push_back(std::make_pair(x, y));
            }
            else if (c == 'C')
            {
                // Cat initial position
                catX = x;
                catY = y;
            }
            else if (c == 'E')
            {
                // End of level marker
                endofgameX = x;
                endofgameY = y;
            }
        }
        x++; // Move to the next column
    }

    levelFile.close();
}

bool Game::CatIsResting()
{
    return catIdleTime > 10;
}

bool Game::GetCatIsOnBlock()
{
    for (const auto &block : blocks)
    {
        if (block.first == catX && block.second == catY + 1)
        {
            return true;
        }
    }
    return false;
}

void Game::Update()
{
    if (gameOver)
    {
        return; // No updates if the game is over.
    }

    // User input updates.
    // Update the cat's position based on the current direction.
    // Move unless blocked by a box.
    int newCatX = catX;
    int newCatY = catY;
    switch (currentDirection)
    {
    case Direction::UP:
        std::cout << "UP" << std::endl;
        if (GetCatIsOnBlock()) {
            // Only jump when on a block.
            catYvelocity -= 4;
        }
        break;
    case Direction::DOWN:
        std::cout << "DOWN" << std::endl;
        catYvelocity += 1;
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

    catXvelocity = std::max(catMinVelocity, std::min(catXvelocity, catMaxVelocity));
    catYvelocity = std::max(catMinVelocity, std::min(catYvelocity, catMaxVelocity));

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
        // Check for collision with end of game.
        if (newCatX == endofgameX && newCatY == endofgameY)
        {
            if (level < maxLevel)
            {
                level++;
                InitGame();
                return;
            }
            else
            {
                std::cout << "You completed the game!" << std::endl;
                gameWon = true;
                gameOver = true;
                level = 0;
            }
            std::cout << "You reached the end of the level." << std::endl;
            break;
        }

        // Check for collisions with food
        for (auto it = food.begin(); it != food.end();)
        {
            if (it->first == newCatX && it->second == newCatY)
            {
                // Food eaten
                it = food.erase(it);
                std::cout << "Food eaten at: (" << newCatX << ", " << newCatY << ")" << std::endl;
            }
            else
            {
                ++it;
            }
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
        // Check for falling ending the game.
        if (newCatY > sizeY)
        {
            gameOver = true;
            level = 0;
            std::cout << "You fell off the level!" << std::endl;
            break;
        }
    }

    // Change cat direction if cat is moving.
    if (catXvelocity > 0)
    {
        catFacingLeft = false;
    }
    else if (catXvelocity < 0)
    {
        catFacingLeft = true;
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

    if (newCatX != catX || newCatY != catY)
    {
        catIdleTime = 0;
    }
    else
    {
        catIdleTime++;
    }
    catX = newCatX;
    catY = newCatY;


}

void Game::ChangeDirection(Direction newDirection)
{
    currentDirection = newDirection;
}
