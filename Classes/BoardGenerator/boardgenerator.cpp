#include "boardgenerator.h"
#include <random>
#include <algorithm>

std::vector<int> BoardGenerator::generateBoard(int n) {
    std::vector<int> randomArray;
    while(true)
    {
        randomArray = getRandomArray(n);
        if(isSolvable(randomArray) && getCorrectness(randomArray) <= MAX_BOARD_CORRECTNESS) break;
    }
    return randomArray;
}

std::vector<int> BoardGenerator::getRandomArray(int n) {
    std::vector<int> randomArray;
    for(int i = 0; i < n * n; i++)
    {
        randomArray.push_back(i);
    }
    std::random_device rd;
    std::mt19937 g(rd());
    shuffle(randomArray.begin(), randomArray.end(), g);
    return randomArray;
}

double BoardGenerator::getCorrectness(std::vector<int> array) {
    int correctlyPlaced = 0;
    for(int i = 0; i < array.size(); i++)
    {
        if(array[i] == 0) continue;
        if(array[i] == i) correctlyPlaced++;
    }
    return ((double)correctlyPlaced) / ((double)(array.size() - 1));
}

bool BoardGenerator::isSolvable(std::vector<int> array) {
    int n = std::sqrt(array.size());
    int inversionCount = getInversionCount<int>(array);
    if(n % 2 == 0)
    {
        int row = std::distance(array.begin(), std::find(array.begin(), array.end(), 0)) / n;
        return (inversionCount % 2 == 0 && row % 2 != 0) || (inversionCount % 2 != 0 && row % 2 == 0);
    }
    else return inversionCount % 2 == 0;
}
