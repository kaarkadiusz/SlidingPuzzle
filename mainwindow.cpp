#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Classes/Game/game.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newGameButton_clicked()
{
    QFrame *frame = ui->frame;
    new Game(frame);
}
