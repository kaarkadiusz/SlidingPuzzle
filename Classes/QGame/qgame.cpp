#include "qgame.h"

QGame::QGame(QFrame* frame) {
    this->Frame = frame;
    this->isInitialized = false;
}

void QGame::init(int n) {
    this->clearLayout();

    QBoard* newBoard = new QBoard(n, this->Frame);
    connect(newBoard, &QBoard::solved, this, &QGame::onBoardSolved);
    newBoard->create();
    newBoard->show(*this->Frame);
    this->BoardObj = newBoard;
    this->isInitialized = true;
}

void QGame::onBoardSolved() {
    PromptDialog *dialog = new PromptDialog(this->Frame);
    dialog->exec();
}

void QGame::clearLayout() {
    QLayout* existingLayout = this->Frame->layout();
    if(existingLayout)
    {
        if(!this->BoardObj->IsSolved)
        {
            YesNoDialog *dialog = new YesNoDialog(this->Frame);
            if(dialog->exec() != 1) return;
        }
        QLayoutItem* item;
        QWidget* widget;
        while ((item = existingLayout->takeAt(0))) {
            if ((widget = item->widget()) != nullptr) {
                delete widget;
            }
        }
        delete existingLayout;
    }
}

void QGame::algorithmSolve() {
    if(!this->isInitialized || this->BoardObj->IsSolved) return;

    std::vector<MoveDirection> moves = this->BoardObj->algorithmSolve();

    for(MoveDirection move : moves) {
        this->tryMove(move);
        Helpers::delay(300);
    }
}
