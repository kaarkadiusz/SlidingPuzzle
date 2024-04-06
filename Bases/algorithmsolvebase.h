#ifndef ALGORITHMSOLVEBASE_H
#define ALGORITHMSOLVEBASE_H

#include <vector>
#include "../enums.h"
#include "../Classes/Block/block.h"

/**
 * @class AlgorithmSolveBase
 * @brief Klasa stanowiąca bazę dla algorytmów rozwiązujących układankę.
 */
class AlgorithmSolveBase
{

protected:
    /**
    * @brief Konwertuje jednowymiarową listę Block* na dwuwymiarową tablicę int.
    *
    * @param blocks Lista klockow, które tworzą planszę.
    */
    static std::vector<std::vector<int>> convertTo2D(std::vector<Block*> blocks);
    /**
    * @brief Sprawdza, czy plansza jako dwuwymiarowa tablica jest w stanie docelowym (czy jest rozwiązana).
    *
    * @param board Dwuwymiarowa tablica int, która tworzy planszę.
    */
    static bool isGoalState(const std::vector<std::vector<int>> &board);

};

#endif // ALGORITHMSOLVEBASE_H
