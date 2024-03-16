#ifndef QGAME_H
#define QGAME_H

#include <QFrame>
#include "../YesNoDialog/yesnodialog.h"
#include "../PromptDialog/promptdialog.h"
#include "qlayout.h"
#include "../Game/game.h"
#include "../../enums.h"

class QGame : public QWidget, public Game{
    Q_OBJECT

public:
    QGame(QFrame* frame);

    void init(int n);
    void tryMove(MoveDirection direction);
    void algorithmSolve();

private:
    QFrame *Frame;
    bool isInitialized;

    void onBoardSolved();
    void clearLayout(QLayout *layout);
};

#endif // QGAME_H
