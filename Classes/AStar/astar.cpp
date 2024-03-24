#include "astar.h"
#include <cmath>
#include <map>
#include <queue>


int AStar::calculateHeuristic(const std::vector<std::vector<int>> &board) {
    int heuristic = 0;
    int n = board.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int value = board[i][j];
            if (value != 0) {
                int targetRow = (value - 1) / n;
                int targetCol = (value - 1) % n;
                heuristic += abs(i - targetRow) + abs(j - targetCol);
            }
        }
    }
    return heuristic;
}

bool AStar::isGoalState(const std::vector<std::vector<int>> &board) {
    int n = board.size();
    int expectedValue = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == n - 1 && j == n - 1) {
                if (board[i][j] != 0) return false;
            } else {
                if (board[i][j] != expectedValue) return false;
                expectedValue++;
            }
        }
    }
    return true;
}

std::vector<PuzzleState> AStar::getNextStates(const PuzzleState &currentState) {
    std::vector<PuzzleState> nextStates;
    int n = currentState.board.size();
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    MoveDirection moves[] = {MoveDirection::Left, MoveDirection::Right, MoveDirection::Up, MoveDirection::Down};
    for (int i = 0; i < 4; ++i) {
        int newX = -1, newY = -1;

        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < n; ++y) {
                if (currentState.board[x][y] == 0) {
                    newX = x + dx[i];
                    newY = y + dy[i];
                    break;
                }
            }
            if (newX != -1) break;
        }

        if (newX >= 0 && newX < n && newY >= 0 && newY < n) {
            std::vector<std::vector<int>> newBoard = currentState.board;
            std::swap(newBoard[newX][newY], newBoard[newX - dx[i]][newY - dy[i]]);
            std::vector<MoveDirection> newMoves = currentState.moves;
            newMoves.push_back(moves[i]);
            PuzzleState nextState(newBoard, currentState.cost + 1, calculateHeuristic(newBoard), newMoves);
            nextStates.push_back(nextState);
        }
    }
    return nextStates;
}

std::vector<MoveDirection> AStar::solvePuzzle(const std::vector<std::vector<int>> &initialState) {
    PuzzleState initialStateObj(initialState, 0, calculateHeuristic(initialState), std::vector<MoveDirection>());

    std::priority_queue<PuzzleState> pq;
    pq.push(initialStateObj);

    std::map<std::vector<std::vector<int>>, int> costSoFar;
    costSoFar[initialState] = 0;

    while (!pq.empty()) {
        PuzzleState currentState = pq.top();
        pq.pop();

        if (isGoalState(currentState.board)) {
            return currentState.moves;
        }

        std::vector<PuzzleState> nextStates = getNextStates(currentState);
        for (const auto &nextState : nextStates) {
            int newCost = currentState.cost + 1;
            if (costSoFar.find(nextState.board) == costSoFar.end() || newCost < costSoFar[nextState.board]) {
                costSoFar[nextState.board] = newCost;
                pq.push(nextState);
            }
        }
    }

    return std::vector<MoveDirection>();
}

std::vector<MoveDirection> AStar::solve(std::vector<Block*> blocks) {
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
    return solvePuzzle(converted);
}
