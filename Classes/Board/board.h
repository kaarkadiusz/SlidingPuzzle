#ifndef BOARD_H
#define BOARD_H

#include "../Block/block.h"
#include <QGridLayout>

class Board : public QGridLayout {
    Q_OBJECT

public:
    Board(int n, QWidget* parent = nullptr);
    void create(QFrame &frame);

private:
    int N;
    std::tuple<int, int> EmptyPosition;
    std::map<Block*, std::tuple<int, int>> Blocks;
    std::vector<std::tuple<int, int>> getRandomPositions();

    void onBlockClicked();
};

#endif // BOARD_H
