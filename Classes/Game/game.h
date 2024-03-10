#ifndef GAME_H
#define GAME_H

#include <QFrame>
#include "../Board/board.h"
#include "../YesNoDialog/yesnodialog.h"
#include "../PromptDialog/promptdialog.h"

class Game : public QObject{
    Q_OBJECT
public:
    Game(QFrame *frame);
    void init(int n);
private:
    QFrame *Frame;
    Board *Board;

    void onBoardSolved();
    void clearLayout(QLayout *layout);
};

#endif // GAME_H
