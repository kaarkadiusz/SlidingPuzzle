#include "boardbase.h"

bool BoardBase::isBlockMovable(Block *block) {
    if(block == nullptr) return false;
    return this->isBlockMovable(block->getPosition());
}

bool BoardBase::isBlockMovable(QBlock *block) {
    if(block == nullptr) return false;
    return this->isBlockMovable(block->getPosition());
}

bool BoardBase::isBlockMovable(std::tuple<int, int> position) {
    if((get<0>(position) == get<0>(this->EmptyPosition) && std::abs(get<1>(position) - get<1>(EmptyPosition)) == 1) ||
        (get<1>(position) == get<1>(this->EmptyPosition) && std::abs(get<0>(position) - get<0>(EmptyPosition)) == 1))
        return true;
    return false;
}

bool BoardBase::isBlockMovable(MoveDirection direction){
    switch(direction)
    {
    case Up:
        if(get<0>(EmptyPosition) == N - 1) return false;
        return true;
    case Down:
        if(get<0>(EmptyPosition) == 0) return false;
        return true;
    case Left:
        if(get<1>(EmptyPosition) == N - 1) return false;
        return true;
    case Right:
        if(get<1>(EmptyPosition) == 0) return false;
        return true;
    }
    return false;
}

void BoardBase::moveBlock(Block *block) {
    std::tuple<int, int> tmpPosition = block->getPosition();
    block->setPosition(EmptyPosition);
    EmptyPosition = tmpPosition;
}

void BoardBase::moveBlock(QBlock *block) {
    std::tuple<int, int> tmpPosition = block->getPosition();
    block->setPosition(EmptyPosition);
    EmptyPosition = tmpPosition;
}

QBlock* BoardBase::findQBlockByPosition(std::vector<QBlock*> blocks, std::tuple<int, int> position) {
    for(QBlock* block : blocks)
    {
        if(block->getPosition() == position) return block;
    }
    return nullptr;
}
