#ifndef QGAME_H
#define QGAME_H

#include <QFrame>
#include <QTimer>
#include "../YesNoDialog/yesnodialog.h"
#include "../PromptDialog/promptdialog.h"
#include "qlayout.h"
#include "../Game/game.h"
#include "../../enums.h"
#include "../QBoard/qboard.h"

/**
 * @class QGame
 * @brief Rozszerzenie graficzne klasy \ref Game.
 */
class QGame : public QWidget, public Game{
    Q_OBJECT

public:
    /**
    * @brief Tworzy obiekt klasy QGame.
    *
    * @param frame Obiekt QFrame z biblioteki qt, w którym będzię rysowana układanka.
    */
    QGame();

    bool init(int n) override;
    void algorithmSolve() override;
    void tryMove(MoveDirection direction) override;
    /**
    * @brief Dodaje planszę jako QWidget w podanym obiekcie QLayout.
    *
    * @param layout Obiekt QLayout, w którym ma zostać dodany QWidget.
    */
    void show(QLayout* layout);
    /**
    * @brief Wstrzymuje stoper, który liczy czas gry.
    */
    void pauseTimer();
    /**
    * @brief Wznawia stoper, który liczy czas gry.
    */
    void resumeTimer();

signals:
    /**
    * @brief Sygnał, przesyłający informacje o aktualnej ilości ruchów, wywoływany w przypadku wykonania ruchu.
    *
    * @param count Wartość licznika ruchów.
    */
    void moveCountChanged(int count);
    /**
    * @brief Sygnał, przesyłający informacje o historii wykonanych ruchów, wywoływany w przypadku wykonania ruchu.
    *
    * @param moveHistory Historia ruchów.
    */
    void moveHistoryChanged(std::vector<MoveDirection> moveHistory);
    /**
    * @brief Sygnał, przesyłający informacje o aktualnym czasie sesji wyrażonym w sekundach, wywoływany co sekundę.
    *
    * @param time Aktualny czas wyrażony w sekundach.
    */
    void timeElapsedChanged(int time);
    /**
    * @brief Sygnał, wysyłany gdy układanka zostanie ułożona.
    */
    void gameSolved();


private slots:
    void onTimeElapsedChanged() override;

private:
    QTimer* Timer;

    void onBlockMoved() override;
    void onBoardSolved();
    bool clearLayout();
};

#endif // QGAME_H
