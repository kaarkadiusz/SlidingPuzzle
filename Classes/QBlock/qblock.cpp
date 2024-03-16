#include "qblock.h"

QBlock::QBlock(int val, std::tuple<int, int> position, QWidget* parent) : Block(val, position), QFrame(parent){
    this->setUi();
}

void QBlock::setUi() {
    this->setFrameShape(QFrame::Box);
    this->setLineWidth(1);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setStyleSheet("background-color: #1a1a1a; color: #fafafa;");

    QLabel* label = new QLabel((new QString("%1"))->arg(this->Val));
    label->setAlignment(Qt::AlignCenter);
    QFont *font = new QFont("Segoe UI", 18);
    label->setFont(*font);
    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(label);

    this->setLayout(layout);
}

void QBlock::mousePressEvent(QMouseEvent* event) {
    emit this->clicked();
}
