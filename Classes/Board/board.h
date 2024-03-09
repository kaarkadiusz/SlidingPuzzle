#ifndef BOARD_H
#define BOARD_H

#include "../Block/block.h"
#include <QGridLayout>

class Board : public QGridLayout {
    Q_OBJECT

public:
    Board(int n, QWidget* parent = nullptr);
    void populate();
    void show(QFrame &frame);

private:
    int N;
    std::vector<std::tuple<int, int>> Positions;
    std::vector<Block> Blocks;
    void onBlockClicked();
};



#endif // BOARD_H
