#pragma once

class Game
{
public:
    Game(int sizeX, int sizeY) : sizeX(sizeX), sizeY(sizeX) {}
    void InitGame();
    void Update();
    bool GameOver();

private:
    const int sizeX, sizeY;
    bool gameOver = false;
};