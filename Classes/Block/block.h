#ifndef BLOCK_H
#define BLOCK_H

#include <tuple>


/**
 * @class Block
 * @brief Klasa pojedynczego klocka.
 */
class Block {
public:
    /**
    * @brief Tworzy obiekt klasy Block.
    *
    * @param val Wartość klocka.
    * @param position Aktualna pozycja klocka.
    */
    Block(int val, std::tuple<int, int> position);
    /**
    * @brief Destruktor klasy Block.
    */
    virtual ~Block();

    /**
    * @brief Sprawdza, czy ten klocek jest w poprawnym miejscu (dla danej długości boku całej planszy).
    *
    * @param n Długość bloku planszy, w której znajduje się klocek.
    *
    * @return Zwraca true jeśli klocek znajduje się w poprawnym miejscu, w przeciwnym przypadku - false.
    */
    bool isPlacedCorrectly(int n);
    /**
    * @brief Zwraca wartość klocka.
    *
    * @return Wartość klocka.
    */
    int getValue();
    /**
    * @brief Zwraca pozycję klocka.
    *
    * @return Pozycja klocka.
    */
    std::tuple<int, int> getPosition();
    /**
    * @brief Ustawia pozycję klocka.
    *
    * @param newPosition Nowa pozycja klocka, która ma zastąpić poprzednią.
    */
    void setPosition(std::tuple<int, int> newPosition);

protected:
    /**
    * @brief Wartość klocka.
    */
    int Value;
    /**
    * @brief Pozycja klocka.
    */
    std::tuple<int, int> Position;
};


#endif // BLOCK_H
