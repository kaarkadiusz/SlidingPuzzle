#ifndef BOARD_H
#define BOARD_H

#include "../BoardBase/boardbase.h"
#include "../QBlock/qblock.h"
#include "qframe.h"
#include <QGridLayout>
#include <random>

#define MAX_BOARD_CORRECTNESS 0.5

class Board : public BoardBase{

public:
    Board(int n);

    void tryMoveBlock(Block* block);
    void create() override;
    void show();

private:
    std::vector<Block*> Blocks;
    bool isBoardSolved() override;
};

#endif // BOARD_H
