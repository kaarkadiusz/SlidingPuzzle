#include "block.h"

Block::Block(int val, std::tuple<int, int> position, int n, QWidget* parent) : QFrame(parent) {
    this->Val = val;
    this->Position = position;
    this->N = n;
    this->isPlacedCorrectly = get<0>(this->Position) * this->N + get<1>(this->Position) == this->Val;

    this->setFrameShape(QFrame::Box);
    this->setLineWidth(1);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setStyleSheet("background-color: #1a1a1a; color: #fafafa;");

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

std::tuple<int, int> Block::getPosition() {
    return this->Position;
}

void Block::setPosition(std::tuple<int, int> newPosition) {
    this->Position = newPosition;
    this->isPlacedCorrectly = get<0>(this->Position) * this->N + get<1>(this->Position) == this->Val;
}
