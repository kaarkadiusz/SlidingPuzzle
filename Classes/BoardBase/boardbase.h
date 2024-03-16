#ifndef BOARDBASE_H
#define BOARDBASE_H

#include "../Block/block.h"
#include "../QBlock/qblock.h"
#include "../BoardGenerator/boardgenerator.h"
#include "../../enums.h"

class BoardBase
{
public:
    bool IsSolved;

protected:
    int N;
    std::tuple<int, int> EmptyPosition;

    virtual bool isBoardSolved() = 0;
    virtual void create() = 0;
    virtual bool tryMoveBlock(MoveDirection direction) = 0;

    Block* findBlockByPosition(std::tuple<int, int> position);
    QBlock* findQBlockByPosition(std::vector<QBlock*> blocks ,std::tuple<int, int> position);

    bool isBlockMovable(Block* block);
    void moveBlock(Block *block);

    bool isBlockMovable(QBlock* block);
    void moveBlock(QBlock *block);

    bool isBlockMovable(MoveDirection direction);

    std::tuple<int, int> getPositionToMove(MoveDirection direction);

private:
    bool isBlockMovable(std::tuple<int, int> position);
};

#endif // BOARDBASE_H
