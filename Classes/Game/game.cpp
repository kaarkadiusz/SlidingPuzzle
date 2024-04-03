#include "game.h"

Game::Game(){
    this->BoardObj = nullptr;
}

bool Game::init(int n) {
    this->BoardObj = new Board(n);
    this->BoardObj->create();
    this->show();

    this->initVariables(n);

    return true;
}

void Game::show() {
    // wypisanie do konsoli
}

void Game::initVariables(int n) {
    this->N = n;
    this->MoveCount = 0;
    this->MoveHistory = std::vector<MoveDirection>();
    this->TimeElapsed = 0;
    this->IsInitialized = true;
    this->IsSolved = false;
}

void Game::tryMove(MoveDirection direction) {
    if(!this->IsInitialized || this->BoardObj->getIsSolved()) return;
    this->BoardObj->tryMove(direction);
}

void Game::algorithmSolve() {
    if(!this->IsInitialized || this->BoardObj->getIsSolved()) return;

    std::vector<MoveDirection> moves = this->BoardObj->algorithmSolve();

    for(MoveDirection move : moves) {
        this->tryMove(move);
        // Helpers::delay(300);
    }
}

void Game::onBlockMoved() {
    this->MoveCount++;
}

void Game::onTimeElapsedChanged() {
    this->TimeElapsed++;
}

int Game::getN() {
    return this->N;
}
