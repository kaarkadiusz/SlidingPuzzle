#ifndef GAME_H
#define GAME_H

#include <QFrame>
#include "../QBoard/qboard.h"
#include "../YesNoDialog/yesnodialog.h"
#include "../PromptDialog/promptdialog.h"

class Game : public QObject{
    Q_OBJECT
public:
    Game(QFrame *frame);
    void init(int n);
private:
    QFrame *Frame;
    QBoard *Board;

    void onBoardSolved();
    void clearLayout(QLayout *layout);
};

#endif // GAME_H
