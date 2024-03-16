#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Classes/QGame/qgame.h"
#include <QMainWindow>
#include <QKeyEvent>

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

private:
    QGame *SlidingPuzzle;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
