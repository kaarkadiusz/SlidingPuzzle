#ifndef BFS_H
#define BFS_H

#include <string>
#include <vector>
#include "../Block/block.h"
#include "../../enums.h"
#include "../../Bases/algorithmsolvebase.h"

class BFS : AlgorithmSolveBase
{
    struct PuzzleState {
        std::vector<std::vector<int>> board;
        std::vector<MoveDirection> moves;
        const PuzzleState* parent;

        PuzzleState(std::vector<std::vector<int>>& b, std::vector<MoveDirection> m, const PuzzleState* p)
            : board(b), moves(m), parent(p) {}

        bool operator==(const PuzzleState& other) const {
            return board == other.board;
        }
    };

public:
    static std::vector<MoveDirection> solve(std::vector<Block*> blocks);

private:
    static std::vector<PuzzleState> getNextStates(const PuzzleState& state);
    static std::vector<MoveDirection> solvePuzzle(std::vector<std::vector<int>>& initialBoard);
};

#endif // BFS_H
