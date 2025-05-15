#pragma once

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

    Game(int sizeX, int sizeY) : sizeX(sizeX), sizeY(sizeY) {}
    void InitGame();
    void ChangeDirection(Direction newDirection);
    void Update();
    bool GameOver();

private:
    const int sizeX, sizeY;
    bool gameOver = false;
    Direction currentDirection = Direction::UP;
};
