#include "qgame.h"

QGame::QGame(QFrame* frame, QObject* parent) : QObject(parent) {
    this->Frame = frame;
}

void QGame::init(int n) {
    auto existingLayout = this->Frame->layout();
    if(existingLayout)
    {
        if(this->Board->IsSolved)
        {
            this->clearLayout(existingLayout);
        }
        else
        {
            YesNoDialog *dialog = new YesNoDialog(this->Frame);
            if(dialog->exec() == 1)
            {
                this->clearLayout(existingLayout);
            }
            else return;
        }
    }
    this->Board = new QBoard(n, this->Frame);
    connect(this->Board, &QBoard::solved, this, &QGame::onBoardSolved);
    this->Board->create(*this->Frame);
}

void QGame::onBoardSolved() {
    PromptDialog *dialog = new PromptDialog(this->Frame);
    dialog->exec();
}

void QGame::clearLayout(QLayout *layout) {
    QLayoutItem* item;
    QWidget* widget;
    while ((item = layout->takeAt(0))) {
        if ((widget = item->widget()) != nullptr) {
            delete widget;
        }
    }
    delete layout;
}
