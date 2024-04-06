#include "algorithmsolvebase.h"
#include <cmath>

bool AlgorithmSolveBase::isGoalState(const std::vector<std::vector<int>> &board) {
    int n = board.size();
    int correctVal = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == n - 1 && j == n - 1) {
                if (board[i][j] != 0) return false;
            } else {
                if (board[i][j] != correctVal++) return false;
            }
        }
    }
    return true;
}

std::vector<std::vector<int>> AlgorithmSolveBase::convertTo2D(std::vector<Block*> blocks) {
    int n = std::sqrt(blocks.size() + 1);
    std::vector<std::vector<int>> converted;
    for(int r = 0; r < n; r ++)
    {
        std::vector<int> row;
        for(int c = 0; c < n; c++)
        {
            row.push_back(0);
        }
        converted.push_back(row);
    }
    for(Block* block : blocks) {
        std::tuple<int, int> position = block->getPosition();
        converted[std::get<0>(position)][std::get<1>(position)] = block->getValue();
    }
    return converted;
}
