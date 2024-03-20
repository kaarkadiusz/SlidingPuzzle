#ifndef QGAME_H
#define QGAME_H

#include <QFrame>
#include "../YesNoDialog/yesnodialog.h"
#include "../PromptDialog/promptdialog.h"
#include "qlayout.h"
#include "../Game/game.h"
#include "../../enums.h"
#include "../QBoard/qboard.h"

class QGame : public QWidget, public Game{
    Q_OBJECT

public:
    QGame(QFrame* frame);

    void init(int n) override;
    void algorithmSolve() override;

signals:
    void blockMoved(int count);

private:
    QFrame* Frame;

    void onBlockMoved();
    void onBoardSolved();
    void clearLayout();
};

#endif // QGAME_H
