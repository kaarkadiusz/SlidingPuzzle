#include "game.h"

Game::Game(){
    this->BoardObj = nullptr;
}

bool Game::init(int n) {
    this->N = n;
    this->BoardObj = new Board(n);
    this->BoardObj->create();
    this->BoardObj->show();
    this->moveCount = 0;
    this->timeElapsed = 0;
    this->isInitialized = true;

    return true;
}

void Game::tryMove(MoveDirection direction) {
    if(!this->isInitialized || this->BoardObj->IsSolved) return;
    this->BoardObj->tryMoveBlock(direction);
}

void Game::algorithmSolve() {
    if(!this->isInitialized || this->BoardObj->IsSolved) return;

    std::vector<MoveDirection> moves = this->BoardObj->algorithmSolve();

    for(MoveDirection move : moves) {
        this->tryMove(move);
        // Helpers::delay(300);
    }
}

void Game::onBlockMoved() {
    this->moveCount++;
}

void Game::onTimeElapsedChanged() {
    this->timeElapsed++;
}

int Game::getN() {
    return this->N;
}
