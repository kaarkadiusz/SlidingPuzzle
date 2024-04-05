#include "qboard.h"

QBoard::QBoard(int n, QWidget* parent) : Board(n), QWidget(parent) {
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->Layout = new QGridLayout();
    this->Layout->setVerticalSpacing(5);
    this->Layout->setHorizontalSpacing(5);
    this->setLayout(this->Layout);
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
        this->Layout->addWidget(block, get<0>(position), get<1>(position));
    }
}

void QBoard::moveBlockWidget(Block* block) {
    QBlock *qblock = dynamic_cast<QBlock*>(block);
    this->Layout->removeWidget(qblock);
    this->Layout->addWidget(qblock, get<0>(block->getPosition()), get<1>(block->getPosition()));
    if(this->IsSolved) {
        emit this->solved();
    }
}

bool QBoard::tryMove(MoveDirection direction) {
    Block* block = this->findBlockByPosition(this->getPositionToMove(direction));
    if(Board::tryMove(direction)) {
        this->moveBlockWidget(block);
        return true;
    }
    else return false;
}

void QBoard::onBlockClicked() {
    if(this->IsSolved) return;
    QBlock *block = dynamic_cast<QBlock*>(sender());
    if(!this->isBlockMovable(block)) return;

    if(this->tryMove(this->getDirectionToMove(block)))
    {
        emit this->blockMoved();
        this->moveBlockWidget(block);
    }
}
