#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFocusPolicy(Qt::StrongFocus);
    this->SlidingPuzzle = new QGame(ui->frame);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newGameButton_clicked()
{
    int n = ui->nSpinBox->value();
    this->SlidingPuzzle->init(n);
}

void MainWindow::on_solveButton_clicked()
{
    this->SlidingPuzzle->algorithmSolve();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left) {
        this->SlidingPuzzle->tryMove(MoveDirection::Left);
    } else if (event->key() == Qt::Key_Right) {
        this->SlidingPuzzle->tryMove(MoveDirection::Right);
    } else if (event->key() == Qt::Key_Up) {
        this->SlidingPuzzle->tryMove(MoveDirection::Up);
    } else if (event->key() == Qt::Key_Down) {
        this->SlidingPuzzle->tryMove(MoveDirection::Down);
    }

    QMainWindow::keyPressEvent(event);
}
