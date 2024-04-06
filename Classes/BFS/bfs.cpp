#include "bfs.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <queue>
#include <map>

std::vector<BFS::PuzzleState> BFS::getNextStates(const PuzzleState& state) {
    std::vector<PuzzleState> nextStates;
    int n = state.board.size();
    std::map<MoveDirection, std::pair<int, int>> directions;
    directions[MoveDirection::Down] = {-1, 0};
    directions[MoveDirection::Up] = {1, 0};
    directions[MoveDirection::Right] = {0, -1};
    directions[MoveDirection::Left] = {0, 1};

    // vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // up, down, left, right
    MoveDirection moves[] = {MoveDirection::Left, MoveDirection::Right, MoveDirection::Up, MoveDirection::Down};
    int blankRow = -1, blankCol = -1;

    // Find the position of the blank space
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (state.board[i][j] == 0) {
                blankRow = i;
                blankCol = j;
                break;
            }
        }
        if (blankRow != -1) break;
    }

    for (const auto& dir : directions) {
        int newRow = blankRow + dir.second.first;
        int newCol = blankCol + dir.second.second;

        if (!(newRow >= 0 && newRow < n && newCol >= 0 && newCol < n)) continue;

        std::vector<std::vector<int>> newBoard = state.board;
        std::swap(newBoard[blankRow][blankCol], newBoard[newRow][newCol]);
        std::vector<MoveDirection> newMoves = state.moves;
        newMoves.push_back(dir.first);
        PuzzleState nextState(newBoard, newMoves, &state);
        nextStates.push_back(nextState);
    }
    return nextStates;
}

std::vector<MoveDirection> BFS::solvePuzzle(std::vector<std::vector<int>>& initialBoard) {
    std::queue<PuzzleState> q;
    std::map<std::vector<std::vector<int>>, int> visited;
    std::vector<MoveDirection> moves;

    PuzzleState initialState(initialBoard, moves, nullptr);
    q.push(initialState);
    visited[initialBoard] = 1;

    while (!q.empty()) {
        PuzzleState currentState = q.front();
        q.pop();

        if (isGoalState(currentState.board)) {
            return currentState.moves;
        }

        std::vector<PuzzleState> nextStates = getNextStates(currentState);
        for (const auto& nextState : nextStates) {
            if (!visited.count(nextState.board)) {
                q.push(nextState);
                visited[nextState.board] = 1;
            }
        }
    }

    return moves;
}

std::vector<MoveDirection> BFS::solve(std::vector<Block*> blocks) {
    std::vector<std::vector<int>> converted = convertTo2D(blocks);
    return solvePuzzle(converted);
}
