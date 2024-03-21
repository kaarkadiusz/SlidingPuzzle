#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFocusPolicy(Qt::StrongFocus);
    this->SlidingPuzzle = new QGame(ui->frame);
    connect(this->SlidingPuzzle, &QGame::moveCountChanged, this, &MainWindow::blockMoved);
    connect(this->SlidingPuzzle, &QGame::timeElapsedChanged, this, &MainWindow::elapsedTimeChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newGameButton_clicked()
{
    int n = this->ui->nSpinBox->value();
    if(this->SlidingPuzzle->init(n)){
        if(n == 3) this->ui->solveButton->setEnabled(true);
        else this->ui->solveButton->setEnabled(false);
    }
}

void MainWindow::on_solveButton_clicked()
{
    if(this->SlidingPuzzle->getN() != 3) return;
    this->SlidingPuzzle->algorithmSolve();
}

void MainWindow::blockMoved(int count) {
    this->ui->moveCountLabel->setText(QString::number(count));
}

void MainWindow::elapsedTimeChanged(int time) {
    this->ui->timeElapsedLabel->setText(QString::fromStdString(Helpers::intToTimeString(time)));
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
