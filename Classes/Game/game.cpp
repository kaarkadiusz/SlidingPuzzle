#include "game.h"

Game::Game(){
    this->BoardObj = nullptr;
}

bool Game::init(int n) {
    this->N = n;
    this->BoardObj = new Board(n);
    this->BoardObj->create();
    this->BoardObj->show();
    this->MoveCount = 0;
    this->MoveHistory = std::vector<MoveDirection>();
    this->TimeElapsed = 0;
    this->IsInitialized = true;

    return true;
}

void Game::tryMove(MoveDirection direction) {
    if(!this->IsInitialized || this->BoardObj->getIsSolved()) return;
    this->BoardObj->tryMoveBlock(direction);
}

void Game::algorithmSolve() {
    if(!this->IsInitialized || this->BoardObj->getIsSolved()) return;

    std::vector<MoveDirection> moves = this->BoardObj->algorithmSolve();

    for(MoveDirection move : moves) {
        this->tryMove(move);
        // Helpers::delay(300);
    }
}

void Game::onBlockMoved(MoveDirection direction) {
    this->MoveCount++;
    this->MoveHistory.push_back(direction);
}

void Game::onTimeElapsedChanged() {
    this->TimeElapsed++;
}

int Game::getN() {
    return this->N;
}
