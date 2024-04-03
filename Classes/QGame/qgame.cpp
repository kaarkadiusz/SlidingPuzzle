#include "qgame.h"

QGame::QGame(QFrame* frame) {
    this->Frame = frame;
    this->IsInitialized = false;
}

bool QGame::init(int n) {
    if(!this->clearLayout()) return false;

    QBoard* newBoard = new QBoard(n, this->Frame);
    connect(newBoard, &QBoard::solved, this, &QGame::onBoardSolved);
    connect(newBoard, &QBoard::blockMoved, this, &QGame::onBlockMoved);
    newBoard->create();
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

    this->initVariables(n);
    this->BoardObj->bindMoveHistory(&this->MoveHistory);
    this->show();
    return true;
}

void QGame::onBoardSolved() {
    if(this->IsSolved) return;
    this->Timer->stop();
    this->IsSolved = true;
    PromptDialog *dialog = new PromptDialog(this->Frame);
    dialog->exec();
}

void QGame::onBlockMoved() {
    Game::onBlockMoved();
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

void QGame::tryMove(MoveDirection direction) {
    QBoard* board = dynamic_cast<QBoard*>(this->BoardObj);
    if(board->tryMove(direction)) emit this->moveHistoryChanged(this->MoveHistory);
}

void QGame::algorithmSolve() {
    if(!this->IsInitialized || this->BoardObj->getIsSolved()) return;

    std::vector<MoveDirection> moves = this->BoardObj->algorithmSolve();

    for(MoveDirection move : moves) {
        this->tryMove(move);
        Helpers::delay(300);
    }
}

void QGame::show() {
    QBoard* board = dynamic_cast<QBoard*>(this->BoardObj);
    this->Frame->setLayout(board);
}


