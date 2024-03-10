#include "game.h"

Game::Game(QFrame *frame){
    this->Frame = frame;
    this->Board = nullptr;
}

void Game::init(int n) {
    auto existingLayout = this->Frame->layout();
    if(existingLayout)
    {
        YesNoDialog *dialog = new YesNoDialog(this->Frame);
        if(dialog->exec() == 1)
        {
            QLayoutItem* item;
            QWidget* widget;
            while ((item = existingLayout->takeAt(0))) {
                if ((widget = item->widget()) != nullptr) {
                    delete widget;
                }
            }
            delete existingLayout;
        }
        else return;
    }
    this->Board = new class Board(n, this->Frame);
    connect(this->Board, &Board::solved, this, &Game::onBoardSolved);
    this->Board->create(*this->Frame);
}

void Game::onBoardSolved() {
    PromptDialog *dialog = new PromptDialog(this->Frame);
    dialog->exec();
}
