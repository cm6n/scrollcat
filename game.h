#pragma once

#include <vector>
#include <utility>

class Game
{
public:
    enum class Direction
    {
        UP,
        RIGHT,
        LEFT,
        DOWN,
        NONE
    };

    enum class GameObject
    {
        CAT,
        BLOCK,
        FOOD
    }; 

    Game(int sizeX, int sizeY) : sizeX(sizeX), sizeY(sizeY) {}
    void InitGame();
    void ChangeDirection(Direction newDirection);
    void Update();
    bool GameOver();
    int GetCatX() const { return catX; }
    int GetCatY() const { return catY; }
    std::vector<std::pair<int, int>> GetFood() const { return food; }
    std::vector<std::pair<int, int>> GetBlocks() const { return blocks; }
    std::pair<int, int> GetEndOfGame() const { return {endofgameX, endofgameY}; }

private:
    const int sizeX, sizeY;
    int catX = 0;
    int catY = 0;
    int catXvelocity = 0;
    int catYvelocity = 0;
    int endofgameX = 0;
    int endofgameY = 0;
    std::vector<std::pair<int, int>> food;
    std::vector<std::pair<int, int>> blocks;
    bool gameOver = false;
    Direction currentDirection = Direction::NONE;

};
