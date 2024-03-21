#include "qgame.h"

QGame::QGame(QFrame* frame) {
    this->Frame = frame;
    this->isInitialized = false;
}

void QGame::init(int n) {
    this->clearLayout();
    this->moveCount = 0;
    this->timeElapsed = 0;

    QBoard* newBoard = new QBoard(n, this->Frame);
    connect(newBoard, &QBoard::solved, this, &QGame::onBoardSolved);
    connect(newBoard, &QBoard::blockMoved, this, &QGame::onBlockMoved);
    newBoard->create();
    newBoard->show(*this->Frame);
    this->BoardObj = newBoard;

    if(this->Timer == nullptr)
    {
        this->Timer = new QTimer(this);
        connect(this->Timer , SIGNAL(timeout()), this, SLOT(onTimeElapsedChanged()));
    }
    else
    {
        this->Timer->stop();
    }
    this->Timer->start(1000);

    emit this->timeElapsedChanged(0);
    emit this->moveCountChanged(0);
    this->isInitialized = true;
}

void QGame::onBoardSolved() {
    this->Timer->stop();
    PromptDialog *dialog = new PromptDialog(this->Frame);
    dialog->exec();
}

void QGame::onBlockMoved() {
    Game::onBlockMoved();
    emit this->moveCountChanged(this->moveCount);
}

void QGame::onTimeElapsedChanged() {
    Game::onTimeElapsedChanged();
    emit this->timeElapsedChanged(this->timeElapsed);
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


