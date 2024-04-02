#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFocusPolicy(Qt::StrongFocus);
    this->SlidingPuzzle = new QGame(ui->frame);
    connect(this->SlidingPuzzle, &QGame::moveCountChanged, this, &MainWindow::moveCountChanged);
    connect(this->SlidingPuzzle, &QGame::moveHistoryChanged, this, &MainWindow::moveHistoryChanged);
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
        this->ui->moveHistoryList->clear();
    }
}

void MainWindow::on_solveButton_clicked()
{
    if(this->SlidingPuzzle->getN() != 3) return;
    this->SlidingPuzzle->algorithmSolve();
}

void MainWindow::moveHistoryChanged(std::vector<MoveDirection> moveHistory) {
    this->ui->moveHistoryList->clear();
    QListWidgetItem *moveItem;
    int i = 1;
    for(MoveDirection move : moveHistory) {
        if(move == MoveDirection::Down) moveItem = new QListWidgetItem(QString("%1. %2").arg(i++).arg("↓"));
        else if(move == MoveDirection::Up) moveItem = new QListWidgetItem(QString("%1. %2").arg(i++).arg("↑"));
        else if(move == MoveDirection::Left) moveItem = new QListWidgetItem(QString("%1. %2").arg(i++).arg("←"));
        else if(move == MoveDirection::Right) moveItem = new QListWidgetItem(QString("%1. %2").arg(i++).arg("→"));
        this->ui->moveHistoryList->addItem(moveItem);
    }
    this->ui->moveHistoryList->scrollToBottom();
}

void MainWindow::moveCountChanged(int count) {
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
