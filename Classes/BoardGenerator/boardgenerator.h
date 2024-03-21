#ifndef BOARDGENERATOR_H
#define BOARDGENERATOR_H

#include<vector>

#define MAX_BOARD_CORRECTNESS 0.5

class BoardGenerator
{
public:
    static std::vector<int> generateBoard(int n);

private:
    template <typename T> static int getInversionCount(std::vector<T> array)
    {
        int inversionCount = 0;
        for(int i = 0; i < array.size(); i++)
        {
            T element = array[i];
            if(element == 0) continue;
            for(int j = i; j < array.size(); j++)
            {
                if (element > array[j] && array[j] != T()) inversionCount++;
            }
        }
        return inversionCount;
    }

    static std::vector<int> getRandomArray(int n);
    static double getCorrectness(std::vector<int> array);
    static bool isSolvable(std::vector<int> array);
};

#endif // BOARDGENERATOR_H
