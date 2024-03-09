#include "game.h"
#include "../Board/board.h"

Game::Game(int n, QFrame *frame){
    this->Frame = frame;
    Board *board = new Board(n, frame);
    board->create(*frame);
}
