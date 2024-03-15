#ifndef QBOARD_H
#define QBOARD_H

#include <QFrame>
#include <QGridLayout>
#include "../Board/board.h"

class QBoard : public QGridLayout, public Board{
    Q_OBJECT

public:
    QBoard(int n, QWidget* parent = nullptr);
    void create(QFrame &frame);

signals:
    void solved();

private:
    void onBlockClicked();


};

#endif // QBOARD_H
