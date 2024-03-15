#include "board.h"

Board::Board(int n) {
    this->N = n;
    this->IsSolved = false;
}

bool Board::isBoardSolved() {
    for(QBlock *block : this->Blocks)
    {
        if(!(block->isPlacedCorrectly(this->N))) return false;
    }
    return true;
}

bool Board::isBlockMovable(QBlock *block) {
    if(block == nullptr) return false;
    std::tuple<int, int> position = block->getPosition();
    if((get<0>(position) == get<0>(this->EmptyPosition) && std::abs(get<1>(position) - get<1>(EmptyPosition)) == 1) ||
       (get<1>(position) == get<1>(this->EmptyPosition) && std::abs(get<0>(position) - get<0>(EmptyPosition)) == 1))
        return true;
    return false;
}

void Board::moveBlock(QBlock *block) {
    std::tuple<int, int> tmpPosition = block->getPosition();
    block->setPosition(EmptyPosition);
    EmptyPosition = tmpPosition;
}
