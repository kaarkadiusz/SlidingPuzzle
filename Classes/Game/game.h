#ifndef GAME_H
#define GAME_H

#include "../Board/board.h"

class Game {

public:
    Game();

    virtual void init(int n);
    void tryMove(MoveDirection direction);
    virtual void algorithmSolve();

protected:
    bool isInitialized;
    Board* BoardObj;
    int moveCount;
    int timeElapsed;

    virtual void onBlockMoved();
    virtual void onTimeElapsedChanged();
};

#endif // GAME_H
