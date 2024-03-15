#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Classes/Game/game.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
