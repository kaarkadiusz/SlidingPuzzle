#ifndef QBOARD_H
#define QBOARD_H

#include <QFrame>
#include <QGridLayout>
#include "../Board/board.h"
#include "../Helpers/helpers.h"

/**
 * @class QBoard
 * @brief Rozszerzenie graficzne klasy \ref Board.
 */
class QBoard : public QGridLayout, public Board{
    Q_OBJECT

public:
    /**
    * @brief Tworzy obiekt klasy QBoard.
    *
    * @param n Długość boku układanki o rozmiarze n x n.
    * @param parent Obiekt klasy QWidget z bibloteki qt, który zostanie rodzicem tworzonego obiektu QBoard.
    */
    QBoard(int n, QWidget* parent = nullptr);

    void create() override;
    /**
    * @brief Metoda, która pozwala na wyświetlenie planszy.
    *
    * @param frame Obiekt klasy QFrame z biblioteki qt, w którym zostanie wyświetlona plansza.
    */
    void show(QFrame &frame);

signals:
    /**
    * @brief Sygnał, informujący o rozwiązaniu układanki.
    */
    void solved();
    /**
    * @brief Sygnał, informujący o wykonaniu ruchu.
    */
    void blockMoved();

private slots:
    void onBlockClicked();

private:
    void moveBlock(Block* block) override;
    void moveBlockWidget(Block* block);
};

#endif // QBOARD_H
