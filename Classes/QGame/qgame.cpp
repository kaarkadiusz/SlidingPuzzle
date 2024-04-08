#include "qgame.h"

QGame::QGame() {
    this->IsInitialized = false;
}

bool QGame::init(int n) {
    // if(!this->clearLayout()) return false;

    QBoard* newBoard = new QBoard(n);
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
    return true;
}

void QGame::onBoardSolved() {
    if(this->IsSolved) return;
    this->Timer->stop();
    this->IsSolved = true;
    emit this->moveCountChanged(this->MoveCount);
    emit this->moveHistoryChanged(this->MoveHistory);
    emit this->gameSolved();
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

bool QGame::tryMove(MoveDirection direction) {
    QBoard* board = dynamic_cast<QBoard*>(this->BoardObj);
    if(board->tryMove(direction)){
        emit this->moveHistoryChanged(this->MoveHistory);
        return true;
    }
    else return false;
}

void QGame::algorithmSolve() {
    if(!this->IsInitialized || this->BoardObj->getIsSolved()) return;
    std::vector<MoveDirection> moves;
    int choice = AlgorithmChoiceDialog().exec();
    if(choice == 0)
    {
        moves = this->BoardObj->algorithmSolve(SolvingAlgorithmName::BFS);
    }
    if(choice == 1)
    {
        moves = this->BoardObj->algorithmSolve(SolvingAlgorithmName::AStar);
    }

    for(MoveDirection move : moves) {
        this->tryMove(move);
        Helpers::delay(300);
    }
}

void QGame::show(QLayout* layout) {
    QBoard* board = dynamic_cast<QBoard*>(this->BoardObj);
    emit this->moveCountChanged(this->MoveCount);
    emit this->moveHistoryChanged(this->MoveHistory);
    emit this->timeElapsedChanged(this->TimeElapsed);
    layout->addWidget(board);
    this->resumeTimer();
}

void QGame::pauseTimer() {
    if(this->Timer != nullptr) this->Timer->stop();
}

void QGame::resumeTimer() {
    if(this->Timer != nullptr && !this->IsSolved) this->Timer->start(1000);
}
