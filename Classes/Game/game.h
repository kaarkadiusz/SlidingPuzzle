#ifndef GAME_H
#define GAME_H

#include "../Board/board.h"

class Game {

public:
    Game();

    virtual bool init(int n);
    virtual void algorithmSolve();
    void tryMove(MoveDirection direction);
    int getN();

protected:
    int N;
    bool IsInitialized;
    Board* BoardObj;
    int MoveCount;
    int TimeElapsed;

    virtual void onBlockMoved();
    virtual void onTimeElapsedChanged();
};

#endif // GAME_H
