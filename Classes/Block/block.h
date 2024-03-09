#ifndef BLOCK_H
#define BLOCK_H

#include <QFrame>
#include <tuple>

class Block : public QFrame {
    Q_OBJECT
public:
    int Val;
    std::tuple<int, int> Position;
    Block(int val, QWidget* parent = nullptr);

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) override;

};


#endif // BLOCK_H
