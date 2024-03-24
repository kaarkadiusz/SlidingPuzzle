#ifndef BOARD_H
#define BOARD_H

#include "../QBlock/qblock.h"
#include "qframe.h"
#include <QGridLayout>
#include <random>
#include "../../enums.h"
#include "../BoardGenerator/boardgenerator.h"
#include "../AStar/astar.h"

class Board{

public:
    Board(int n);
    virtual ~Board();

    virtual void create();
    virtual void show();
    bool tryMoveBlock(Block* block);
    bool tryMoveBlock(MoveDirection direction);
    std::vector<MoveDirection> algorithmSolve();
    bool getIsSolved();

protected:
    int N;
    bool IsSolved;
    std::tuple<int, int> EmptyPosition;
    std::vector<Block*> Blocks;

    Block* findBlockByPosition(std::tuple<int, int> position);
    bool isBoardSolved();
    bool isBlockMovable(Block* block);
    bool isBlockMovable(MoveDirection direction);
    std::tuple<int, int> getPositionToMove(MoveDirection direction);
    virtual void moveBlock(Block* block);
};

#endif // BOARD_H
