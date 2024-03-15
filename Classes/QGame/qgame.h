#ifndef QGAME_H
#define QGAME_H

#include <QFrame>
#include "../YesNoDialog/yesnodialog.h"
#include "../PromptDialog/promptdialog.h"
#include "qlayout.h"
#include "../Game/game.h"

class QGame : public QObject, public Game{
    Q_OBJECT

public:
    QGame(QFrame* frame, QObject *parent = nullptr);

    void init(int n);

private:
    void onBoardSolved();
    void clearLayout(QLayout *layout);
    QFrame *Frame;
};

#endif // QGAME_H
