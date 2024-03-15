#ifndef BOARD_H
#define BOARD_H

#include "../QBlock/qblock.h"
#include "qframe.h"
#include <QGridLayout>
#include <random>

#define MAX_BOARD_CORRECTNESS 0.5

class Board {

public:
    Board(int n);
    bool IsSolved;

protected:
    int N;
    std::vector<QBlock*> Blocks;
    std::tuple<int, int> EmptyPosition;

    bool isBlockMovable(QBlock *block);
    void moveBlock(QBlock *block);
    bool isBoardSolved();
};

#endif // BOARD_H
