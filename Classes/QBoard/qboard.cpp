#include "qboard.h"
#include "../BoardGenerator/boardgenerator.h"

QBoard::QBoard(int n, QWidget* parent) : Board(n), QGridLayout(parent) {
    this->setVerticalSpacing(5);
    this->setHorizontalSpacing(5);
}

void QBoard::create(QFrame &frame) {
    this->Blocks.clear();
    std::vector<Block*> board = BoardGenerator::generateBoard(this->N);
    int emptyElement = this->N * this->N - 1;

    for(Block* block : board)
    {
        std::tuple<int, int> position = block->getPosition();
        int val = block->getVal();
        if(val == emptyElement)
        {
            this->EmptyPosition = position;
            continue;
        }
        QBlock* qblock = new QBlock(val, position, nullptr);
        connect(qblock, &QBlock::clicked, this, &QBoard::onBlockClicked);
        this->Blocks.push_back(qblock);
        this->addWidget(qblock, get<0>(position), get<1>(position));
        delete block;
    }
    frame.setLayout(this);
}

void QBoard::onBlockClicked() {
    QBlock *block = dynamic_cast<QBlock*>(sender());
    if(!isBlockMovable(block) || this->IsSolved) return;

    this->removeWidget(block);
    this->addWidget(block, get<0>(EmptyPosition), get<1>(EmptyPosition));
    this->moveBlock(block);
    if(this->isBoardSolved())
    {
        this->IsSolved = true;
        emit this->solved();
    }
}
