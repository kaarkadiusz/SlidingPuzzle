#ifndef ALGORITHMSOLVEBASE_H
#define ALGORITHMSOLVEBASE_H

#include <vector>
#include "../enums.h"
#include "../Classes/Block/block.h"

class AlgorithmSolveBase
{

protected:
    static std::vector<std::vector<int>> convertTo2D(std::vector<Block*> blocks);
    static bool isGoalState(const std::vector<std::vector<int>> &board);
};

#endif // ALGORITHMSOLVEBASE_H
