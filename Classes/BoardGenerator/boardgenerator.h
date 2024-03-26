#ifndef BOARDGENERATOR_H
#define BOARDGENERATOR_H

#include<vector>

#define MAX_BOARD_CORRECTNESS 0.5

/**
 * @class BoardGenerator
 * @brief Klasa, która służy do generowania poprawnej planszy.
 */
class BoardGenerator
{
public:
    /**
    * @brief Generuje planszę o długości boku n.
    *
    * Ściślej tworzy kontener losowo rozmieszczonych liczb całkowitych o wartościach od 0 do n - 1 o rozmiarze n * n.
    * Tak utworzony kontener można następnie wykorzystać do utworzenia planszy złożonej z klocków gdzie kolejny klocek
    * (idąc wpierw kolumnami a następnie wierszami) przyjmuje wartości kolejnych liczb całkowitych z kontenera.
    * Utworzenie planszy w ten sposób zapewnia rozwiązywalność układanki.
    *
    * <b> Należy pamiętać że wartość 0 w generowanym kontenerze oznacza miejsce puste. </b>
    *
    * @param n Długość boku planszy.
    *
    * @return Kontener liczb całkowitych, które można wykorzystać do stworzenia planszy układanki z przesuwanych klocków.
    */
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
