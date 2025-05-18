#pragma once

#include <vector>
#include <utility>

class Game
{
public:
    typedef enum Direction
    {
        DIRECTION_NONE = 0,
        DIRECTION_UP = 0x0001,
        DIRECTION_RIGHT = 0b0010,
        DIRECTION_LEFT = 0b0100,
        DIRECTION_DOWN = 0b1000
    } Direction_t;

    enum class GameObject
    {
        CAT,
        BLOCK,
        FOOD
    };

    Game(int sizeX, int sizeY) : sizeX(sizeX), sizeY(sizeY) {}
    void InitGame();
    void ChangeDirection(Direction_t newDirection);
    void Update();
    bool GameOver() { return gameOver; }
    bool GameWon() { return gameWon; }
    int GetCatX() const { return catX; }
    int GetCatY() const { return catY; }
    bool GetCatIsOnBlock();
    bool CatIsResting();
    bool CatIsFacingLeft() const { return catFacingLeft; }
    std::vector<std::pair<int, int>> GetFood() const { return food; }
    std::vector<std::pair<int, int>> GetBlocks() const { return blocks; }
    std::pair<int, int> GetEndOfGame() const { return {endofgameX, endofgameY}; }
    std::pair<int, int> GetCatVelocity() const { return {catXvelocity, catYvelocity}; }
    int GetLevel() const { return level; }
    int GetScore() const { return score; }

private:
    const int sizeX, sizeY;
    int level = 0;
    const int maxLevel = 2;
    int score = 0;
    int catX = 0;
    int catY = 0;
    int catXvelocity = 0;
    int catYvelocity = 0;
    const int catMaxVelocity = 5;
    const int catMinVelocity = -5;
    int catIdleTime = 0;
    int endofgameX = 0;
    int endofgameY = 0;
    std::vector<std::pair<int, int>> food;
    std::vector<std::pair<int, int>> blocks;
    bool gameOver = false;
    bool gameWon = false;
    Direction_t currentDirection = DIRECTION_NONE;
    bool catFacingLeft = false;
};
