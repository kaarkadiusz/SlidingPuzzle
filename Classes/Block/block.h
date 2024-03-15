#ifndef BLOCK_H
#define BLOCK_H

#include <tuple>

class Block {
public:
    Block(int val, std::tuple<int, int> position);

    std::tuple<int, int> getPosition();
    void setPosition(std::tuple<int, int> newPosition);
    bool isPlacedCorrectly(int n);

protected:
    int Val;
    std::tuple<int, int> Position;
};


#endif // BLOCK_H
