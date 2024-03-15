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

    std::vector<int> generateBoard();
    bool isBlockMovable(QBlock *block);
    void moveBlock(QBlock *block);
    bool isBoardSolved();

private:
    std::vector<int> getRandomArray();
    int getArrayInversionCount(std::vector<int> array);
    double getArrayCorrectness(std::vector<int> array);
    bool isBoardSolvable(std::vector<int> array);

};

#endif // BOARD_H
