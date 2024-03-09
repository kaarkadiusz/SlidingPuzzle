#ifndef GAME_H
#define GAME_H

#include <QFrame>


class Game
{
public:
    Game(QFrame *frame);
    void init(int n);
private:
    QFrame *Frame;
};

#endif // GAME_H
