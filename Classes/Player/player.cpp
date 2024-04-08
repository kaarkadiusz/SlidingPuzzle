#include "player.h"


Player::Player() {
    this->Games = std::map<std::string, Game*>();
}

std::map<std::string, bool> Player::getGamesKeys() {
    std::map<std::string, bool> result;
    for(std::string game : this->GamesKeys) {
        result[game] = this->Games[game]->getIsSolved();
    }
    return result;
}
