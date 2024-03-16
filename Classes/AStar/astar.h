#ifndef ASTAR_H
#define ASTAR_H

#include <string>
#include <vector>
#include "qdebug.h"
#include <map>
#include <queue>
#include "../Block/block.h"
#include "../QBlock/qblock.h"
#include "../../enums.h"

struct PuzzleState {
    std::vector<std::vector<int>> board;
    int cost;
    int heuristic;
    std::vector<MoveDirection> moves;

    PuzzleState(std::vector<std::vector<int>> b, int c, int h, std::vector<MoveDirection> m) : board(b), cost(c), heuristic(h), moves(m) {}

    bool operator<(const PuzzleState &other) const {
        return cost + heuristic > other.cost + other.heuristic;
    }
};

class AStar
{
public:
    static std::vector<MoveDirection> solve(std::vector<Block*> blocks);
    static std::vector<MoveDirection> solve(std::vector<QBlock*> blocks);

private:
    static int calculateHeuristic(const std::vector<std::vector<int>> &board);
    static bool isGoalState(const std::vector<std::vector<int>> &board);
    static std::vector<PuzzleState> getNextStates(const PuzzleState &currentState);
    static std::vector<MoveDirection> solvePuzzle(const std::vector<std::vector<int>> &initialState);
};

#endif // ASTAR_H
