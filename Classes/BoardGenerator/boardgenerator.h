#ifndef BOARDGENERATOR_H
#define BOARDGENERATOR_H

#include<vector>

#define MAX_BOARD_CORRECTNESS 0.5

class BoardGenerator
{
public:
    static std::vector<int> generateBoard(int n);

private:
    static std::vector<int> getRandomArray(int n);
    static int getInversionCount(std::vector<int> array);
    static double getCorrectness(std::vector<int> array);
    static bool isSolvable(std::vector<int> array);
};

#endif // BOARDGENERATOR_H
