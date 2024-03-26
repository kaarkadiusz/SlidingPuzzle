#ifndef QBLOCK_H
#define QBLOCK_H

#include "qframe.h"
#include "qboxlayout.h"
#include "qlabel.h"

#include "../Block/block.h"

/**
 * @class QBlock
 * @brief Rozszerzenie graficzne klasy \ref Block.
 */
class QBlock : public QFrame, public Block{
    Q_OBJECT

public:
    /**
    * @brief Tworzy obiekt klasy QBlock.
    *
    * @param val Wartość klocka.
    * @param position Aktualna pozycja klocka.
    * @param parent Obiekt klasy QWidget z bibloteki qt, który zostanie rodzicem tworzonego obiektu QBlock.
    */
    QBlock(int val, std::tuple<int, int> position, QWidget* parent = nullptr);

signals:
    /**
    * @brief Sygnał, informujący o zdarzeniu kliknięcia w klocek przez użytkownika.
    */
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    void setUi();
};

#endif // QBLOCK_H
