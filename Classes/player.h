#ifndef PLAYER_H
#define PLAYER_H

#include "Game/game.h"
#include "QGame/qgame.h"


/**
 * @class Player
 * @brief Klasa, która jest reprezentacją gracza.
 */
class Player
{
public:
    Player();
    /**
    * @brief Szablon, który tworzy nową grę Sliding Block Puzzle. Dostępne klasy to 'Game' oraz 'QGame'.
    *
    * @param n Długość boku układanki.
    *
    * @return Obiekt o wybranym typie ('Game*' lub 'QGame*').
    */
    template <typename T, typename std::enable_if<std::is_same<T, Game>::value || std::is_same<T, QGame>::value, int>::type = 0> T* newGame(int n)
    {
        T *game = new T();
        game->init(n);
        std::string key = "Gra #" + std::to_string(this->Games.size() + 1);
        this->Games[key] = game;
        this->GamesKeys.push_back(key);
        return game;
    }
    /**
    * @brief Szablon, który zwracą utworzoną już grę Sliding Block Puzzle. Dostępne klasy to 'Game' oraz 'QGame'.
    *
    * @param key Klucz gry, dla którego zostanie zwrócony obiekt.
    *
    * @return Obiekt o wybranym typie ('Game*' lub 'QGame*').
    */
    template <typename T, typename std::enable_if<std::is_same<T, Game>::value || std::is_same<T, QGame>::value, int>::type = 0> T* getGame(std::string key)
    {
        if(this->Games.find(key) == this->Games.end()) throw std::invalid_argument("Wrong key");
        return (T*)this->Games[key];
    }
    /**
    * @brief Zwraca, słownik gier, które posiada ten obiekt.
    * Klucze w słowniku są kluczami gier, wartościami są informacje o tym, czy układanka powiązana z danym kluczem została rozwiązana.
    *
    * @return Obiekt o wybranym typie ('Game*' lub 'QGame*').
    */
    std::map<std::string, bool> getGamesKeys();

private:
    std::map<std::string, Game*> Games;
    std::vector<std::string> GamesKeys;
};

#endif // PLAYER_H
