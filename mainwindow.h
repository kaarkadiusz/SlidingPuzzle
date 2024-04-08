#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Classes/QGame/qgame.h"
#include <QMainWindow>
#include <QKeyEvent>
#include "Classes/Helpers/helpers.h"
#include "Classes/Player/player.h"
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_newGameButton_clicked();
    void on_solveButton_clicked();
    void moveHistoryChanged(std::vector<MoveDirection> moveHistory);
    void moveCountChanged(int count);
    void elapsedTimeChanged(int time);
    void switchGame(QListWidgetItem *item);
    void onCurrentGameSolved();

private:
    QGame* CurrentGame;
    Ui::MainWindow *ui;
    QBoxLayout *Layout;
    Player *Player;

    void clearFrame();
    void setupGameList();
};
#endif // MAINWINDOW_H
