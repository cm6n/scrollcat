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
        DOWN
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

private:
    const int sizeX, sizeY;
    int catX = 0;
    int catY = 0;
    std::vector<std::pair<int, int>> food;
    std::vector<std::pair<int, int>> blocks;
    bool gameOver = false;
    Direction currentDirection = Direction::UP;

};
