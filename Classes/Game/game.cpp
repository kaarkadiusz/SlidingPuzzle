#include "game.h"

Game::Game(){
    this->BoardObj = nullptr;
}

void Game::init(int n) {
    this->BoardObj = new Board(n);
    this->BoardObj->create();
    this->BoardObj->show();
    this->isInitialized = true;
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
