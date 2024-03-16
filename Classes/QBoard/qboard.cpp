#include "qboard.h"

QBoard::QBoard(int n, QWidget* parent) : QGridLayout(parent) {
    this->N = n;
    this->IsSolved = false;
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
        QBlock* qblock = new QBlock(val, position, nullptr);
        connect(qblock, &QBlock::clicked, this, &QBoard::onBlockClicked);
        this->Blocks.push_back(qblock);
        this->addWidget(qblock, get<0>(position), get<1>(position));
    }
}

void QBoard::show(QFrame &frame) {
    frame.setLayout(this);
}

void QBoard::onBlockClicked() {
    QBlock *block = dynamic_cast<QBlock*>(sender());
    if(this->IsSolved) return;
    if(this->tryMoveBlock(block))
    {
        this->removeWidget(block);
        this->addWidget(block, get<0>(block->getPosition()), get<1>(block->getPosition()));
        if(this->isBoardSolved())
        {
            this->IsSolved = true;
            emit this->solved();
        }
    }
}

bool QBoard::isBoardSolved() {
    for(QBlock *block : this->Blocks)
    {
        if(!(block->isPlacedCorrectly(this->N))) return false;
    }
    return true;
}

bool QBoard::tryMoveBlock(QBlock* block){
    if(this->isBlockMovable(block)){
        this->moveBlock(block);
        return true;
    }
    else return false;
}

bool QBoard::tryMoveBlock(MoveDirection direction){
    if(!this->isBlockMovable(direction)) return false;

    QBlock* block = findQBlockByPosition(this->Blocks, this->getPositionToMove(direction));
    if(block == nullptr) return false;

    if(this->tryMoveBlock(block))
    {
        this->removeWidget(block);
        this->addWidget(block, get<0>(block->getPosition()), get<1>(block->getPosition()));
        if(this->isBoardSolved())
        {
            this->IsSolved = true;
            emit this->solved();
        }
        return true;
    }
    else return false;
}

std::vector<MoveDirection> QBoard::algorithmSolve() {
    return  AStar::solve(this->Blocks);
}
