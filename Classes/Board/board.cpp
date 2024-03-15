#include "board.h"

Board::Board(int n) {
    this->N = n;
    this->IsSolved = false;
}

bool Board::isBoardSolved() {
    for(QBlock *block : this->Blocks)
    {
        if(!(block->isPlacedCorrectly(this->N))) return false;
    }
    return true;
}

std::vector<int> Board::generateBoard() {
    std::vector<int> randomArray;
    while(true)
    {
        randomArray = this->getRandomArray();
        if(this->isBoardSolvable(randomArray) && this->getArrayCorrectness(randomArray) <= MAX_BOARD_CORRECTNESS) break;
    }
    return randomArray;
}

double Board::getArrayCorrectness(std::vector<int> array) {
    int emptyElement = this->N * this->N - 1;
    int correctlyPlaced = 0;
    for(int i = 0; i < array.size(); i++)
    {
        if(array[i] == emptyElement) continue;
        if(array[i] == i) correctlyPlaced++;
    }
    return ((double)correctlyPlaced) / ((double)(array.size() - 1));
}

bool Board::isBoardSolvable(std::vector<int> array) {
    int inversionCount = this->getArrayInversionCount(array);
    if(this->N % 2 == 0)
    {
        int row = std::distance(array.begin(), std::find(array.begin(), array.end(), this->N * this->N - 1)) / this->N;
        return (inversionCount % 2 == 0 && row % 2 != 0) || (inversionCount % 2 != 0 && row % 2 == 0);
    }
    else return inversionCount % 2 == 0;
}

int Board::getArrayInversionCount(std::vector<int> array) {
    int inversionCount = 0;
    int emptyElement = this->N * this->N - 1;
    for(int i = 0; i < array.size(); i++)
    {
        int element = array[i];
        if(element == emptyElement) continue;
        for(int j = i; j < array.size(); j++)
        {
            if (element > array[j] && array[j] != emptyElement) inversionCount++;
        }
    }
    return inversionCount;
}

std::vector<int> Board::getRandomArray() {
    std::vector<int> randomArray;
    for(int i = 0; i < this->N * this->N; i++)
    {
        randomArray.push_back(i);
    }
    std::random_device rd;
    std::mt19937 g(rd());
    shuffle(randomArray.begin(), randomArray.end(), g);
    return randomArray;
}

bool Board::isBlockMovable(QBlock *block) {
    if(block == nullptr) return false;
    std::tuple<int, int> position = block->getPosition();
    if((get<0>(position) == get<0>(this->EmptyPosition) && std::abs(get<1>(position) - get<1>(EmptyPosition)) == 1) ||
       (get<1>(position) == get<1>(this->EmptyPosition) && std::abs(get<0>(position) - get<0>(EmptyPosition)) == 1))
        return true;
    return false;
}

void Board::moveBlock(QBlock *block) {
    std::tuple<int, int> tmpPosition = block->getPosition();
    block->setPosition(EmptyPosition);
    EmptyPosition = tmpPosition;

}
