#include "block.h"
#include "qboxlayout.h"
#include "qlabel.h"

Block::Block(int val, QWidget* parent) : QFrame(parent) {
    this->Val = val;
    this->setFrameShape(QFrame::Box);
    this->setLineWidth(1);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setStyleSheet("background-color: #b4d4ff; color: #1a1a1a;");

    QLabel* label = new QLabel((new QString("%1"))->arg(this->Val + 1));
    label->setAlignment(Qt::AlignCenter);
    QFont *font = new QFont("Segoe UI", 18);
    label->setFont(*font);
    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(label);
    this->setLayout(layout);
}

void Block::mousePressEvent(QMouseEvent* event) {
    emit this->clicked();
}
