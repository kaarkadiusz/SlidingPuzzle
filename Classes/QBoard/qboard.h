#ifndef QBOARD_H
#define QBOARD_H

#include <QFrame>
#include <QGridLayout>
#include "../BoardBase/boardbase.h"

class QBoard : public QGridLayout, public BoardBase{
    Q_OBJECT

public:
    QBoard(int n, QWidget* parent = nullptr);

    bool tryMoveBlock(QBlock* block);
    bool tryMoveBlock(MoveDirection direction) override;
    void create() override;
    void show(QFrame &frame);

signals:
    void solved();

private:
    std::vector<QBlock*> Blocks;
    bool isBoardSolved() override;
    void onBlockClicked();
};

#endif // QBOARD_H
