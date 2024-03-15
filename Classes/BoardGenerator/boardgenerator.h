#ifndef BOARDGENERATOR_H
#define BOARDGENERATOR_H

#include<vector>
#include "../Block/block.h"

#define MAX_BOARD_CORRECTNESS 0.5

class BoardGenerator
{
public:
    static std::vector<Block*> generateBoard(int n);

private:
    static std::vector<int> getRandomArray(int n);
    static int getInversionCount(std::vector<int> array);
    static double getCorrectness(std::vector<int> array);
    static bool isSolvable(std::vector<int> array);
    static std::vector<Block*> convertIntsToBlocks(std::vector<int> array);
};

#endif // BOARDGENERATOR_H
