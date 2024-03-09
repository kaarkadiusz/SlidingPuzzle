#include "board.h"
#include <random>

Board::Board(int n, QWidget* parent) : QGridLayout(parent) {
    this->N = n;
    this->setVerticalSpacing(5);
    this->setHorizontalSpacing(5);
    for(int i = 0; i < this->N*this->N ; i++) {
        this->Positions.push_back(std::tuple(i / 3, i % 3));
    }
    std::random_device rd;
    std::mt19937 g(rd());
    shuffle(Positions.begin(), Positions.end(), g);
    Positions.pop_back();
}

void Board::populate() {
    this->Blocks.clear();

    int i = 0;
    for(auto tuple : Positions)
    {
        auto block = new Block(i, nullptr);
        connect(block, &Block::clicked, this, &Board::onBlockClicked);
        this->addWidget(block, get<0>(tuple), get<1>(tuple));
        i++;
    }
}

void Board::show(QFrame &frame) {
    frame.setLayout(this);
}

void Board::onBlockClicked() {
    Block* clickedBlock = dynamic_cast<Block*>(sender());
    if (clickedBlock) {
        qDebug() << "Block " << clickedBlock->Val << " clicked.";
    }
}
