#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include "../Block/block.h"
#include "../../enums.h"
#include "../../Bases/algorithmsolvebase.h"

/**
 * @class AStar
 * @brief Klasa, która służy do automatycznego rozwiązania planszy.
 */
class AStar : AlgorithmSolveBase
{
    struct PuzzleState {
        std::vector<std::vector<int>> board;
        int cost;
        int heuristic;
        std::vector<MoveDirection> moves;

        PuzzleState(std::vector<std::vector<int>> b, int c, int h, std::vector<MoveDirection> m)
            : board(b), cost(c), heuristic(h), moves(m) {}

        bool operator<(const PuzzleState &other) const {
            return cost + heuristic > other.cost + other.heuristic;
        }
    };

public:
    /**
    * @brief Wykorzystuje algorytm A* do znalezienia optymalnego rozwiązania układanki.
    *
    * @param blocks Kontener klocków. Reprezentacja planszy jako kontener obiektów klasy Block.
    *
    * @return Kontener zapełniony wartościami enum, których wykonanie w ustalonej sekwencji (od początku do końca kontenera) prowadzi do rozwiązania układanki.
    */
    static std::vector<MoveDirection> solve(std::vector<Block*> blocks);

private:
    static int calculateHeuristic(const std::vector<std::vector<int>> &board);
    static std::vector<PuzzleState> getNextStates(const PuzzleState &currentState);
    static std::vector<MoveDirection> solvePuzzle(const std::vector<std::vector<int>> &initialState);
};

#endif // ASTAR_H
