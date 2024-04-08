#include "board.h"

Board::Board(int n) {
    this->N = n;
    this->MoveHistory = nullptr;
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

bool Board::tryMove(MoveDirection direction) {
    if(!this->isBlockMovable(direction)) return false;

    this->move(direction);
    return true;
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
    if(this->IsSolved) return true;
    for(Block *block : this->Blocks)
    {
        if(!(block->isPlacedCorrectly(this->N))) return false;
    }
    this->IsSolved = true;
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

MoveDirection Board::getDirectionToMove(Block* block){
    std::tuple<int, int> position = block->getPosition();
    if(get<0>(position) == get<0>(this->EmptyPosition) && get<1>(position) == get<1>(this->EmptyPosition) + 1) return MoveDirection::Left;
    if(get<0>(position) == get<0>(this->EmptyPosition) && get<1>(position) == get<1>(this->EmptyPosition) - 1) return MoveDirection::Right;
    if(get<0>(position) == get<0>(this->EmptyPosition) + 1 && get<1>(position) == get<1>(this->EmptyPosition)) return MoveDirection::Up;
    if(get<0>(position) == get<0>(this->EmptyPosition) - 1 && get<1>(position) == get<1>(this->EmptyPosition)) return MoveDirection::Down;
    throw std::invalid_argument("Provided block is not movable");;
}

void Board::move(MoveDirection direction) {
    if(this->MoveHistory != nullptr) this->MoveHistory->push_back(direction);
    Block* block = this->findBlockByPosition(this->getPositionToMove(direction));
    std::tuple<int, int> tmpPosition = block->getPosition();
    block->setPosition(EmptyPosition);
    this->EmptyPosition = tmpPosition;
    this->isBoardSolved();
}

void Board::bindMoveHistory(std::vector<MoveDirection> *moveHistory) {
    this->MoveHistory = moveHistory;
}

std::vector<MoveDirection> Board::algorithmSolve(SolvingAlgorithmName algorithm) {
    if(algorithm == SolvingAlgorithmName::AStar)
    {
        return AStar::solve(this->Blocks);
    }
    if(algorithm == SolvingAlgorithmName::BFS)
    {
        return BFS::solve(this->Blocks);
    }
    return std::vector<MoveDirection>();
}

bool Board::getIsSolved(){
    return this->IsSolved;
}
