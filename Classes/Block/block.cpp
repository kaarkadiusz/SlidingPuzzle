#include "block.h"
#include "qboxlayout.h"
#include "qlabel.h"

Block::Block(int val, QWidget* parent) : QFrame(parent) {
    this->Val = val;
    this->setFrameShape(QFrame::Box);
    this->setLineWidth(1);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setStyleSheet("background-color: #40a2d8; color: #1a1a1a;");

    QLabel* label = new QLabel((new QString("%1"))->arg(this->Val + 1));
    label->setAlignment(Qt::AlignCenter);
    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(label);
    this->setLayout(layout);
}

void Block::mousePressEvent(QMouseEvent* event) {
    emit this->clicked();
}
