#include "game.h"
#include "../Board/board.h"

Game::Game(QFrame *frame){
    this->Frame = frame;
    Board *board = new Board(3, frame);
    board->create(*frame);
}
