#ifndef QBLOCK_H
#define QBLOCK_H

#include "qframe.h"
#include "qboxlayout.h"
#include "qlabel.h"

#include "../Block/block.h"

class QBlock : public QFrame, public Block{
    Q_OBJECT

public:
    QBlock(int val, std::tuple<int, int> position, QWidget* parent = nullptr);

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    void setUi();
};

#endif // QBLOCK_H
