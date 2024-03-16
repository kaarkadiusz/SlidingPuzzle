#ifndef QBOARD_H
#define QBOARD_H

#include <QFrame>
#include <QGridLayout>
#include "../Board/board.h"
#include "../Helpers/helpers.h"

class QBoard : public QGridLayout, public Board{
    Q_OBJECT

public:
    QBoard(int n, QWidget* parent = nullptr);

    void create() override;
    void show(QFrame &frame);
    std::vector<MoveDirection> algorithmSolve();

signals:
    void solved();

private:
    void moveBlock(Block* block) override;
    void moveBlockWidget(Block* block);
    void onBlockClicked();
};

#endif // QBOARD_H
