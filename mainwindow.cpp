#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFocusPolicy(Qt::StrongFocus);
    this->Player = new class Player();
    this->Layout = new QBoxLayout(QBoxLayout::TopToBottom);
    this->ui->frame->setLayout(this->Layout);
    connect(this->ui->gamesList, &QListWidget::itemClicked, this, &MainWindow::switchGame);
    // this->CurrentGame = new QGame();
    // connect(this->CurrentGame, &QGame::moveCountChanged, this, &MainWindow::moveCountChanged);
    // connect(this->CurrentGame, &QGame::moveHistoryChanged, this, &MainWindow::moveHistoryChanged);
    // connect(this->CurrentGame, &QGame::timeElapsedChanged, this, &MainWindow::elapsedTimeChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::switchGame(QListWidgetItem *key) {
    this->clearFrame();
    this->CurrentGame->pauseTimer();
    QGame* game = this->Player->getGame<QGame>(key->text().toStdString());
    this->CurrentGame = game;
    this->setupGameList();
    this->CurrentGame->show(this->Layout);
}

void MainWindow::on_newGameButton_clicked()
{
    this->clearFrame();
    if(this->CurrentGame != nullptr) this->CurrentGame->pauseTimer();
    int n = this->ui->nSpinBox->value();
    QGame* game = this->Player->newGame<QGame>(n);
    this->CurrentGame = game;
    connect(this->CurrentGame, &QGame::moveCountChanged, this, &MainWindow::moveCountChanged);
    connect(this->CurrentGame, &QGame::moveHistoryChanged, this, &MainWindow::moveHistoryChanged);
    connect(this->CurrentGame, &QGame::timeElapsedChanged, this, &MainWindow::elapsedTimeChanged);
    connect(this->CurrentGame, &QGame::gameSolved, this, &MainWindow::onCurrentGameSolved);
    this->setupGameList();
    this->CurrentGame->show(this->Layout);
}

void MainWindow::onCurrentGameSolved() {
    this->setupGameList();
    PromptDialog *dialog = new PromptDialog();
    dialog->exec();
}

void MainWindow::on_solveButton_clicked()
{
    if(this->CurrentGame->getN() != 3) return;
    this->CurrentGame->algorithmSolve();
}

void MainWindow::setupGameList() {
    this->ui->gamesList->clear();
    for(auto &pair : this->Player->getGamesKeys())
    {
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(pair.first));
        if(this->CurrentGame == Player->getGame<QGame>(pair.first)) item->setBackground(QColor::fromRgb(204, 255, 255));
        else if(pair.second) item->setBackground(QColor::fromRgb(119, 255, 51));
        this->ui->gamesList->addItem(item);
    }
}

void MainWindow::moveHistoryChanged(std::vector<MoveDirection> moveHistory) {
    this->ui->moveHistoryList->clear();
    QListWidgetItem *moveItem;
    int i = 1;
    for(MoveDirection move : moveHistory) {
        if(move == MoveDirection::Down) moveItem = new QListWidgetItem(QString("%1. %2").arg(i++).arg("↓"));
        else if(move == MoveDirection::Up) moveItem = new QListWidgetItem(QString("%1. %2").arg(i++).arg("↑"));
        else if(move == MoveDirection::Left) moveItem = new QListWidgetItem(QString("%1. %2").arg(i++).arg("←"));
        else moveItem = new QListWidgetItem(QString("%1. %2").arg(i++).arg("→"));
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
        this->CurrentGame->tryMove(MoveDirection::Left);
    } else if (event->key() == Qt::Key_Right) {
        this->CurrentGame->tryMove(MoveDirection::Right);
    } else if (event->key() == Qt::Key_Up) {
        this->CurrentGame->tryMove(MoveDirection::Up);
    } else if (event->key() == Qt::Key_Down) {
        this->CurrentGame->tryMove(MoveDirection::Down);
    }

    QMainWindow::keyPressEvent(event);
}

void MainWindow::clearFrame() {
    QLayoutItem *item;
    while ((item = this->Layout->takeAt(0)) != nullptr) {
        QWidget* widget = item->widget();
        this->Layout->removeWidget(widget);
        widget->setParent(nullptr);
    }
}
