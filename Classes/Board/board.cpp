#include "board.h"
#include <random>

Board::Board(int n, QWidget* parent) : QGridLayout(parent) {
    this->N = n;
    this->setVerticalSpacing(5);
    this->setHorizontalSpacing(5);
}

void Board::create(QFrame &frame) {
    this->Blocks.clear();
    std::vector<std::tuple<int, int>> positions = this->getRandomPositions();

    for(int i = 0; i < positions.size() - 1; i++)
    {
        Block *block = new Block(i, nullptr);
        connect(block, &Block::clicked, this, &Board::onBlockClicked);
        this->Blocks[block] = positions[i];
        this->addWidget(block, get<0>(positions[i]), get<1>(positions[i]));
    }

    this->EmptyPosition = positions[positions.size() - 1];

    frame.setLayout(this);
}

std::vector<std::tuple<int, int>> Board::getRandomPositions(){
    std::vector<std::tuple<int, int>> positions;
    for(int i = 0; i < this->N*this->N ; i++) {
        positions.push_back(std::tuple(i / this->N, i % this->N));
    }
    std::random_device rd;
    std::mt19937 g(rd());
    shuffle(positions.begin(), positions.end(), g);

    return positions;
}

void Board::onBlockClicked() {
    Block *block = dynamic_cast<Block*>(sender());
    if(!isBlockMovable(block)) return;
    moveBlock(block);
}

bool Board::isBlockMovable(Block *block) {
    if(block == nullptr) return false;
    std::tuple<int, int> position = this->Blocks.at(block);
    if((get<0>(position) == get<0>(this->EmptyPosition) && std::abs(get<1>(position) - get<1>(EmptyPosition)) == 1) ||
       (get<1>(position) == get<1>(this->EmptyPosition) && std::abs(get<0>(position) - get<0>(EmptyPosition)) == 1))
        return true;
    return false;
}

void Board::moveBlock(Block *block) {
    this->removeWidget(block);
    this->addWidget(block, get<0>(EmptyPosition), get<1>(EmptyPosition));
    std::swap(this->Blocks.at(block), EmptyPosition);
}
