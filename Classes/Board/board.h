#ifndef BOARD_H
#define BOARD_H

#include "../QBlock/qblock.h"
#include "qframe.h"
#include <QGridLayout>
#include <random>
#include "../../enums.h"
#include "../BoardGenerator/boardgenerator.h"
#include "../AStar/astar.h"


/**
 * @class Board
 * @brief Klasa planszy, na której są rozmieszczone klocki.
 */
class Board{

public:
    /**
    * @brief Tworzy obiekt klasy Board.
    *
    * @param n Długość boku układanki o rozmiarze n x n.
    */
    Board(int n);
    /**
    * @brief Destruktor klasy Board.
    */
    virtual ~Board();

    /**
    * @brief Generuje planszę, czyli losowo zapełnia kontener \ref Blocks.
    */
    virtual void create();
    /**
    * @brief Metoda, która pozwala na wyświetlenie planszy.
    */
    virtual void show();
    /**
    * @brief Wykonuje próbę ruchu klocka w zadanym kierunku.
    *
    * @param block Klocek, którego pozycja ma zostać zmieniona.
    *
    * @return Zwraca true jeśli klocek został przemieszczony pomyślnie, w przeciwnym przypadku - false.
    */
    bool tryMoveBlock(Block* block);
    /**
    * @brief Wykonuje próbę ruchu klocka w zadanym kierunku.
    *
    * @param direction Wartość enum, która wskazuje na kierunek w jakim ma zostać przesunięty klocek.
    *
    * @return Zwraca true jeśli klocek został przemieszczony pomyślnie, w przeciwnym przypadku - false.
    */
    bool tryMoveBlock(MoveDirection direction);
    /**
    * @brief Wykonuje algorytm automatycznego rozwiązania układanki.
    *
    * @return Kontener zapełniony wartościami enum, których wykonanie w ustalonej sekwencji (od początku do końca kontenera) prowadzi do rozwiązania układanki.
    */
    std::vector<MoveDirection> algorithmSolve();
    /**
    * @brief Zwraca informację o tym, czy układanka została rozwiązana.
    *
    * @return Wartość bool gdzie: true - jeśli układanka została rozwiązana lub false w przeciwnym przypadku.
    */
    bool getIsSolved();

protected:
    /**
    * @brief Długość boku układanki.
    */
    int N;
    /**
    * @brief Informacja o tym, czy układanka została rozwiązana.
    */
    bool IsSolved;
    /**
    * @brief Aktualna pozycja miejsca pustego na planszy.
    */
    std::tuple<int, int> EmptyPosition;
    /**
    * @brief Kontener trzymający wszystkie obiekty klasy Block, które znajdują się na planszy.
    */
    std::vector<Block*> Blocks;

    /**
    * @brief Metoda zwracająca klocek znajdujący się w podanym miejscu na planszy.
    *
    * @param positon Krotka, określająca pozycję na planszy, dla której ma zostać zwrócony klocek.
    *
    * @return Klocek w przypadku pomyślnego znalezienia w określonej pozycji lub nullptr - w przeciwnym przypadku.
    */
    Block* findBlockByPosition(std::tuple<int, int> position);
    /**
    * @brief Metoda sprawdzająca czy układanka została rozwiązana.
    *
    * @return Wartość true jeśli układanka została rozwiązana, w przeciwnym przypadku - false.
    */
    bool isBoardSolved();
    /**
    * @brief Metoda sprawdzająca czy dany klocek może zmienić pozycję.
    *
    * @param block Klocek, dla którego należy sprawdzić, czy jego pozycja może zostać zmieniona.
    *
    * @return Wartość true jeśli podany klocek może zmienić pozycję, w przeciwnym przypadku - false.
    */
    bool isBlockMovable(Block* block);
    /**
    * @brief Metoda sprawdzająca czy dany ruch jest wykonalny.
    *
    * Sprawdza, czy ruch w podaną stronę jest wykonalny. Ściślej sprawdza, czy ruch w podanym kierunku jest możliwy w stosunku do pozycji miejsca pustego na planszy.
    *
    * @param direction Wartość enum, która wskazuje na kierunek w jakim ma zostać przesunięty klocek.
    *
    * @return Wartość true jeśli podany ruch jest możliwy, w przeciwnym przypadku - false.
    */
    bool isBlockMovable(MoveDirection direction);
    /**
    * @brief Metoda wyliczająca pozycję klocka, który należy przesunąć przy korzystaniu z metody \ref MoveBlock().
    *
    * @param direction Wartość enum, która wskazuje na kierunek w jakim ma zostać przesunięty klocek.
    *
    * @return Pozycja klocka, który należy przesunąć.
    */
    std::tuple<int, int> getPositionToMove(MoveDirection direction);
    /**
    * @brief Metoda zmieniająca pozycję klocka.
    *
    * Metoda, która służy do poruszenia klockiem na planszy. Zmienia pozycję klocka, wartość \ref EmptyPosition oraz inkrementuje licznik ruchów.
    *
    * @param block Klocek, który zostanie przesunięty.
    */
    virtual void moveBlock(Block* block);
};

#endif // BOARD_H
