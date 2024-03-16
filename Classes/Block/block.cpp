#include "block.h"

Block::Block(int val, std::tuple<int, int> position){
    this->Val = val;
    this->Position = position;
}

Block::~Block() {

}

std::tuple<int, int> Block::getPosition() {
    return this->Position;
}

void Block::setPosition(std::tuple<int, int> newPosition) {
    this->Position = newPosition;
}

bool Block::isPlacedCorrectly(int n){
    return std::get<0>(this->Position) * n + std::get<1>(this->Position) == this->Val - 1;
}

int Block::getVal() {
    return this->Val;
}
