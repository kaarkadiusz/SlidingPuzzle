#ifndef PROMPTDIALOG_H
#define PROMPTDIALOG_H

#include <QDialog>

namespace Ui {
class PromptDialog;
}

/**
 * @class PromptDialog
 * @brief Klasa, która tworzy prosty dialog.
 */
class PromptDialog : public QDialog
{
    Q_OBJECT

public:
    /**
    * @brief Tworzy obiekt klasy PromptDialog.
    *
    * @param parent Obiekt klasy QWidget z bibloteki qt, który zostanie rodzicem tworzonego obiektu PromptDialog.
    */
    explicit PromptDialog(QWidget *parent = nullptr);
    /**
    * @brief Destruktor klasy PromptDialog.
    */
    ~PromptDialog();

private:
    Ui::PromptDialog *ui;
};


#endif // PROMPTDIALOG_H
