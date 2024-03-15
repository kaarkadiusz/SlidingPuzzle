#include "qboard.h"

QBoard::QBoard(int n, QWidget* parent) : Board(n), QGridLayout(parent) {
    this->setVerticalSpacing(5);
    this->setHorizontalSpacing(5);
}

void QBoard::create(QFrame &frame) {
    this->Blocks.clear();
    std::vector<int> board = this->generateBoard();
    int emptyElement = this->N * this->N - 1;

    for(int i = 0; i < board.size(); i++)
    {
        std::tuple<int, int> thisIterationPosition = std::tuple(i / this->N, i % this->N);
        if(board[i] == emptyElement)
        {
            this->EmptyPosition = thisIterationPosition;
            continue;
        }
        QBlock *block = new QBlock(board[i], thisIterationPosition, nullptr);
        connect(block, &QBlock::clicked, this, &QBoard::onBlockClicked);

        this->Blocks.push_back(block);
        this->addWidget(block, i / this->N, i % this->N);
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
