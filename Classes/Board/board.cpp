#include "board.h"
#include <random>

Board::Board(int n, QWidget* parent) : QGridLayout(parent) {
    this->N = n;
    this->setVerticalSpacing(5);
    this->setHorizontalSpacing(5);
}

void Board::create(QFrame &frame) {
    this->Blocks.clear();
    this->CorrectlyPlacedBlocks = 0;
    std::vector<int> board = this->generateBoard();
    int emptyElement = this->N * this->N - 1;

    for(int i = 0; i < board.size(); i++)
    {
        if(board[i] == emptyElement)
        {
            this->EmptyPosition = std::tuple(i / this->N, i % this->N);
            continue;
        }
        Block *block = new Block(board[i], nullptr);
        connect(block, &Block::clicked, this, &Board::onBlockClicked);
        this->Blocks[block] = std::tuple(i / this->N, i % this->N);
        this->addWidget(block, i / this->N, i % this->N);
    }
    frame.setLayout(this);
}

std::vector<int> Board::generateBoard() {
    std::vector<int> randomArray;
    while(true)
    {
        randomArray = this->getRandomArray();
        if(this->isBoardSolvable(randomArray) && this->getBoardCorrectness(randomArray) <= MAX_BOARD_CORRECTNESS) break;
    }
    return randomArray;
}

double Board::getBoardCorrectness() {
    int correctlyPlaced = 0;
    for(auto pair : this->Blocks)
    {
        if(pair.first->Val == get<0>(pair.second) * this->N + get<1>(pair.second)) correctlyPlaced++;
    }
    return ((double)correctlyPlaced) / ((double)(this->Blocks.size()));
}

double Board::getBoardCorrectness(std::vector<int> array) {
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

void Board::onBlockClicked() {
    Block *block = dynamic_cast<Block*>(sender());
    if(!isBlockMovable(block)) return;
    moveBlock(block);
}

bool Board::isBlockMovable(Block *block) {
    if(block == nullptr) return false;
    std::tuple<int, int> position = this->Blocks.at(block);
    if((get<0>(position) == get<0>(this->EmptyPosition) && std::abs(get<1>(position) - get<1>(EmptyPosition)) == 1) ||
       (get<1>(position) == get<1>(this->EmptyPosition) && std::abs(get<0>(position) - get<0>(EmptyPosition)) == 1))
        return true;
    return false;
}

void Board::moveBlock(Block *block) {
    this->removeWidget(block);
    this->addWidget(block, get<0>(EmptyPosition), get<1>(EmptyPosition));
    std::swap(this->Blocks.at(block), EmptyPosition);
    if(this->getBoardCorrectness() == 1) emit this->solved();
}
