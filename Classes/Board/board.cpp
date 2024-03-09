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
    Block *clickedBlock = dynamic_cast<Block*>(sender());
    auto value = this->Blocks.at(clickedBlock);
    if (clickedBlock) {
        qDebug() << "Block " << clickedBlock->Val << "( " << get<0>(value) << " , "<< get<1>(value) << " ) clicked.";
        qDebug() << get<0>(EmptyPosition) << " , "<< get<1>(EmptyPosition);
    }
}
