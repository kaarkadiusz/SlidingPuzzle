#include "board.h"

Board::Board(int n, QWidget* parent) : QGridLayout(parent) {
    this->N = n;
    this->IsSolved = false;

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
        std::tuple<int, int> thisIterationPosition = std::tuple(i / this->N, i % this->N);
        if(board[i] == emptyElement)
        {
            this->EmptyPosition = thisIterationPosition;
            continue;
        }
        Block *block = new Block(board[i], thisIterationPosition, this->N, nullptr);
        connect(block, &Block::clicked, this, &Board::onBlockClicked);

        this->Blocks.push_back(block);
        this->addWidget(block, i / this->N, i % this->N);
    }
    frame.setLayout(this);
}

bool Board::isBoardSolved() {
    for(Block *block : this->Blocks)
    {
        if(!(block->isPlacedCorrectly)) return false;
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

void Board::onBlockClicked() {
    Block *block = dynamic_cast<Block*>(sender());
    if(!isBlockMovable(block) || this->IsSolved) return;
    moveBlock(block);
}

bool Board::isBlockMovable(Block *block) {
    if(block == nullptr) return false;
    std::tuple<int, int> position = block->getPosition();
    if((get<0>(position) == get<0>(this->EmptyPosition) && std::abs(get<1>(position) - get<1>(EmptyPosition)) == 1) ||
       (get<1>(position) == get<1>(this->EmptyPosition) && std::abs(get<0>(position) - get<0>(EmptyPosition)) == 1))
        return true;
    return false;
}

void Board::moveBlock(Block *block) {
    this->removeWidget(block);
    this->addWidget(block, get<0>(EmptyPosition), get<1>(EmptyPosition));
    std::tuple<int, int> tmpPosition = block->getPosition();
    block->setPosition(EmptyPosition);
    EmptyPosition = tmpPosition;
    if(this->isBoardSolved())
    {
        this->IsSolved = true;
        emit this->solved();
    }
}
