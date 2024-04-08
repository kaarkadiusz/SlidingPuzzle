#ifndef ALGORITHMCHOICEDIALOG_H
#define ALGORITHMCHOICEDIALOG_H

#include <QDialog>

namespace Ui {
class AlgorithmChoiceDialog;
}

/**
 * @class AlgorithmChoiceDialog
 * @brief Klasa, która tworzy prosty dialog do wyboru algorytmu rozwiązującego układankę, z przyciskami 'AStar' i 'BFS'.
 */
class AlgorithmChoiceDialog : public QDialog
{
    Q_OBJECT

public:
    /**
    * @brief Tworzy obiekt klasy AlgorithmChoiceDialog.
    *
    * @param parent Obiekt klasy QWidget z bibloteki qt, który zostanie rodzicem tworzonego obiektu AlgorithmChoiceDialog.
    */
    explicit AlgorithmChoiceDialog(QWidget *parent = nullptr);
    /**
    * @brief Destruktor klasy AlgorithmChoiceDialog.
    */
    ~AlgorithmChoiceDialog();

private:
    Ui::AlgorithmChoiceDialog *ui;
};

#endif // ALGORITHMCHOICEDIALOG_H
