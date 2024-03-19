#include "qboard.h"

QBoard::QBoard(int n, QWidget* parent) : Board(n), QGridLayout(parent) {
    this->N = n;
    this->setVerticalSpacing(5);
    this->setHorizontalSpacing(5);
}

void QBoard::create() {
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
        QBlock* block = new QBlock(val, position, nullptr);
        connect(block, &QBlock::clicked, this, &QBoard::onBlockClicked);
        this->Blocks.push_back(block);
        this->addWidget(block, get<0>(position), get<1>(position));
    }
}

void QBoard::show(QFrame &frame) {
    frame.setLayout(this);
}

void QBoard::moveBlock(Block *block) {
    std::tuple<int, int> tmpPosition = block->getPosition();
    block->setPosition(EmptyPosition);
    EmptyPosition = tmpPosition;
    this->moveBlockWidget(block);
}

void QBoard::moveBlockWidget(Block* block) {
    QBlock *qblock = dynamic_cast<QBlock*>(block);
    this->removeWidget(qblock);
    this->addWidget(qblock, get<0>(block->getPosition()), get<1>(block->getPosition()));
    if(this->isBoardSolved())
    {
        this->IsSolved = true;
        emit this->solved();
    }
}

void QBoard::onBlockClicked() {
    if(this->IsSolved) return;
    QBlock *block = dynamic_cast<QBlock*>(sender());
    this->tryMoveBlock(block);
}
