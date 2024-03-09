#include "game.h"
#include "../Board/board.h"
#include "../PromptDialog/promptdialog.h"

Game::Game(QFrame *frame){
    this->Frame = frame;
}

void Game::init(int n) {
    auto existingLayout = this->Frame->layout();
    if(existingLayout)
    {
        PromptDialog *dialog = new PromptDialog(this->Frame);
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
    Board *board = new Board(n, this->Frame);
    board->create(*this->Frame);
}
