#include "board.h"

Board::Board(int n) {
    this->N = n;
    this->IsSolved = false;
}

void Board::create() {
    this->Blocks.clear();
    std::vector<int> board = BoardGenerator::generateBoard(this->N);

    for(int i = 0; i < board.size(); i++)
    {
        std::tuple<int, int> position = std::tuple<int, int>(i / this->N, i % this->N);
        int val = board[i];
        if(val == 0)
        {
            this->EmptyPosition = position;
            continue;
        }
        Block* block = new Block(val, position);
        this->Blocks.push_back(block);
    }
}

void Board::show() {
    // wypisanie do konsoli
}

void Board::tryMoveBlock(Block* block){
    if(this->isBlockMovable(block)) this->moveBlock(block);
}

bool Board::isBoardSolved() {
    for(Block *block : this->Blocks)
    {
        if(!(block->isPlacedCorrectly(this->N))) return false;
    }
    return true;
}
