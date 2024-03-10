#ifndef BLOCK_H
#define BLOCK_H

#include <QFrame>
#include "qboxlayout.h"
#include "qlabel.h"

class Block : public QFrame {
    Q_OBJECT
public:
    Block(int val, std::tuple<int, int> position, int N, QWidget* parent = nullptr);
    bool isPlacedCorrectly;

    std::tuple<int, int> getPosition();
    void setPosition(std::tuple<int, int> newPosition);

private:
    int Val;
    std::tuple<int, int> Position;
    int N;

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) override;

};


#endif // BLOCK_H
