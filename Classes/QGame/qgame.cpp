#include "qgame.h"

QGame::QGame(QFrame* frame) {
    this->Frame = frame;
    this->IsInitialized = false;
}

bool QGame::init(int n) {
    if(!this->clearLayout()) return false;
    this->N = n;
    this->MoveCount = 0;
    this->MoveHistory = std::vector<MoveDirection>();
    this->TimeElapsed = 0;

    QBoard* newBoard = new QBoard(n, this->Frame);
    connect(newBoard, &QBoard::solved, this, &QGame::onBoardSolved);
    connect(newBoard, &QBoard::blockMoved, this, &QGame::onBlockMoved);
    newBoard->create();
    newBoard->show(*this->Frame);
    this->BoardObj = newBoard;

    if(this->Timer == nullptr || !this->IsInitialized)
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
    this->IsInitialized = true;
    return true;
}

void QGame::onBoardSolved() {
    this->Timer->stop();
    PromptDialog *dialog = new PromptDialog(this->Frame);
    dialog->exec();
}

void QGame::onBlockMoved(MoveDirection direction) {
    Game::onBlockMoved(direction);
    emit this->moveCountChanged(this->MoveCount);
    emit this->moveHistoryChanged(this->MoveHistory);
}

void QGame::onTimeElapsedChanged() {
    Game::onTimeElapsedChanged();
    emit this->timeElapsedChanged(this->TimeElapsed);
}

bool QGame::clearLayout() {
    QLayout* existingLayout = this->Frame->layout();
    if(existingLayout)
    {
        if(!this->BoardObj->getIsSolved())
        {
            YesNoDialog *dialog = new YesNoDialog(this->Frame);
            if(dialog->exec() != 1) return false;
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
    return true;
}

void QGame::algorithmSolve() {
    if(!this->IsInitialized || this->BoardObj->getIsSolved()) return;

    std::vector<MoveDirection> moves = this->BoardObj->algorithmSolve();

    for(MoveDirection move : moves) {
        this->tryMove(move);
        Helpers::delay(300);
    }
}


