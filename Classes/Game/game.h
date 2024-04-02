#ifndef GAME_H
#define GAME_H

#include "../Board/board.h"


/**
 * @class Game
 * @brief Główna klasa umożliwiająca grę w układankę.
 *
 * Klasa Game pozwala na inicjalizację i interakcję z układanką z przesuwanych klocków. <br />
 * Po stworzeniu obiektu klasy Game należy wykonać metodę \ref init() aby zainicjować układankę o rozmiarze n x n. <br />
 * Następenie można wykonywać ruchy przy pomocy metody \ref tryMove().
 */
class Game {

public:
    /**
    * @brief Tworzy obiekt klasy Game.
    */
    Game();

    /**
    * @brief Inicjalizuje układankę o rozmiarze n x n.
    *
    *
    * @param n Bok układanki.
    * @return Wartość true jeśli pomyślnie zainicjalizowano nową układankę, w przeciwnym wypadku - wartość false.
    */
    virtual bool init(int n);
    /**
    * @brief Wykonuje algorytm automatycznego rozwiązania układanki.
    */
    virtual void algorithmSolve();
    /**
    * @brief Wykonuje próbę ruchu klocka w zadanym kierunku.
    *
    * @param direction Wartość enum, która wskazuje na kierunek w jakim chcemy przesunąć klocek.
    */
    void tryMove(MoveDirection direction);
    /**
    * @brief Zwraca długość boku układanki n x n.
    *
    * @return Długość boku układanki.
    */
    int getN();

protected:
    /**
    * @brief Długość boku układanki.
    */
    int N;
    /**
    * @brief Wartość bool wskazująca na to, czy układanka została zainicjalizowana.
    */
    bool IsInitialized;
    /**
    * @brief Obiekt planszy.
    */
    Board* BoardObj;
    /**
    * @brief Licznik ruchów wykonanych w danej sesji.
    */
    int MoveCount;
    /**
    * @brief Licznik czasu sprędzonego w danej sesji w sekundach.
    */
    int TimeElapsed;
    /**
    * @brief Historia wykonanych ruchów.
    */
    std::vector<MoveDirection> MoveHistory;

    /**
    * @brief Metoda, która aktualizuje licznik ruchów.
    */
    virtual void onBlockMoved(MoveDirection direction);
    /**
    * @brief Metoda, która aktualizuje licznik czasu.
    */
    virtual void onTimeElapsedChanged();
};

#endif // GAME_H
