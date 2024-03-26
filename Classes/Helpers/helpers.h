#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include <iomanip>

/**
 * @class Helpers
 * @brief Klasa, która zawiera funkcje pomocnicze.
 */
class Helpers
{
public:
    /**
    * @brief Usypia wykonanie w qt.
    *
    * @param milliseconds Czas, na jaki ma zostać uśpione wykonanie wyrażony w milisekundach.
    */
    static void delay( int milliseconds );
    /**
    * @brief Konwertuje liczbę sekund na ciąg znaków oznaczających czas wyrażony w formacie MM:SS.
    *
    * @param s Liczba sekund, którą należy przekonwertować.
    *
    * @return Ciąg znaków oznaczający czas wyrażony w formacie MM:SS.
    */
    static std::string intToTimeString(int s);
};

#endif // HELPERS_H
