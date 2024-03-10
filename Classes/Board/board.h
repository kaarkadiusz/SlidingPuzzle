#ifndef BOARD_H
#define BOARD_H

#include "../Block/block.h"
#include <QGridLayout>
#include <random>

#define MAX_BOARD_CORRECTNESS 0.5

class Board : public QGridLayout {
    Q_OBJECT

public:
    Board(int n, QWidget* parent = nullptr);
    void create(QFrame &frame);
    bool IsSolved;

signals:
    void solved();

private:
    int N;
    std::tuple<int, int> EmptyPosition;
    std::vector<Block*> Blocks;
    int CorrectlyPlacedBlocks;

    std::vector<int> getRandomArray();
    std::vector<int> generateBoard();
    int getArrayInversionCount(std::vector<int> array);
    double getArrayCorrectness(std::vector<int> array);
    bool isBoardSolved();
    bool isBoardSolvable(std::vector<int> array);
    bool isBlockMovable(Block *block);
    void onBlockClicked();
    void moveBlock(Block *block);

};

#endif // BOARD_H
