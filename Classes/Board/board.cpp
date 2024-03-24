#include "board.h"

Board::Board(int n) {
    this->N = n;
    this->IsSolved = false;
}

Board::~Board() {

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

bool Board::tryMoveBlock(Block* block){
    if(!this->isBlockMovable(block)) return false;

    this->moveBlock(block);
    return true;
}

bool Board::tryMoveBlock(MoveDirection direction) {
    if(!this->isBlockMovable(direction)) return false;

    Block* block = findBlockByPosition(this->getPositionToMove(direction));
    if(block == nullptr) return false;

    this->moveBlock(block);
    return true;
}

void Board::show() {
    // wypisanie do konsoli
}

Block* Board::findBlockByPosition(std::tuple<int, int> position) {
    for(Block* block : this->Blocks)
    {
        std::tuple<int, int> blockPosition = block->getPosition();
        if(get<0>(blockPosition) == get<0>(position) && get<1>(blockPosition) == get<1>(position)) return block;
    }
    return nullptr;
}

bool Board::isBoardSolved() {
    for(Block *block : this->Blocks)
    {
        if(!(block->isPlacedCorrectly(this->N))) return false;
    }
    return true;
}

bool Board::isBlockMovable(Block *block) {
    if(block == nullptr) return false;
    std::tuple<int, int> position = block->getPosition();
    if((get<0>(position) == get<0>(this->EmptyPosition) && std::abs(get<1>(position) - get<1>(EmptyPosition)) == 1) ||
        (get<1>(position) == get<1>(this->EmptyPosition) && std::abs(get<0>(position) - get<0>(EmptyPosition)) == 1))
        return true;
    return false;
}

bool Board::isBlockMovable(MoveDirection direction){
    if( (direction == MoveDirection::Up && get<0>(this->EmptyPosition) == this->N - 1) ||
        (direction == MoveDirection::Down && get<0>(this->EmptyPosition) == 0) ||
        (direction == MoveDirection::Left && get<1>(this->EmptyPosition) == this->N - 1) ||
        (direction == MoveDirection::Right && get<1>(this->EmptyPosition) == 0) )
        return false;
    else return true;
}

std::tuple<int, int> Board::getPositionToMove(MoveDirection direction) {
    if(direction == MoveDirection::Up) return std::tuple<int, int> (get<0>(this->EmptyPosition) + 1, get<1>(this->EmptyPosition));
    if(direction == MoveDirection::Down) return std::tuple<int, int> (get<0>(this->EmptyPosition) - 1, get<1>(this->EmptyPosition));
    if(direction == MoveDirection::Left) return std::tuple<int, int> (get<0>(this->EmptyPosition), get<1>(this->EmptyPosition) + 1);
    if(direction == MoveDirection::Right) return std::tuple<int, int> (get<0>(this->EmptyPosition), get<1>(this->EmptyPosition) - 1);
    return std::tuple<int, int>(-1, -1);
}

void Board::moveBlock(Block *block) {
    std::tuple<int, int> tmpPosition = block->getPosition();
    block->setPosition(EmptyPosition);
    this->EmptyPosition= tmpPosition;
}

std::vector<MoveDirection> Board::algorithmSolve() {
    return AStar::solve(this->Blocks);
}

bool Board::getIsSolved(){
    return this->IsSolved;
}
