#ifndef QGAME_H
#define QGAME_H

#include <QFrame>
#include <QTimer>
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

    bool init(int n) override;
    void algorithmSolve() override;

signals:
    void moveCountChanged(int count);
    void timeElapsedChanged(int time);

private slots:
    void onTimeElapsedChanged() override;

private:
    QFrame* Frame;
    QTimer* Timer;

    void onBlockMoved() override;
    void onBoardSolved();
    bool clearLayout();
};

#endif // QGAME_H
