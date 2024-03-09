#include "block.h"
#include "qboxlayout.h"
#include "qlabel.h"

Block::Block(int val, QWidget* parent) : QFrame(parent) {
    this->Val = val;
    this->setFrameShape(QFrame::Box);
    this->setLineWidth(1);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QLabel* label = new QLabel((new QString("%1"))->arg(this->Val));
    label->setAlignment(Qt::AlignCenter);
    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(label);
    this->setLayout(layout);
}

void Block::mousePressEvent(QMouseEvent* event) {
    emit this->clicked();
}
