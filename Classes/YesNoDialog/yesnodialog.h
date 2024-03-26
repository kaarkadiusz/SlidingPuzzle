#ifndef YESNODIALOG_H
#define YESNODIALOG_H

#include <QDialog>

namespace Ui {
class YesNoDialog;
}

/**
 * @class YesNoDialog
 * @brief Klasa, która tworzy prosty dialog z przyciskami 'Tak' i 'Nie'.
 */
class YesNoDialog : public QDialog
{
    Q_OBJECT

public:
    /**
    * @brief Tworzy obiekt klasy YesNoDialog.
    *
    * @param parent Obiekt klasy QWidget z bibloteki qt, który zostanie rodzicem tworzonego obiektu YesNoDialog.
    */
    explicit YesNoDialog(QWidget *parent = nullptr);
    /**
    * @brief Destruktor klasy YesNoDialog.
    */
    ~YesNoDialog();

private:
    Ui::YesNoDialog *ui;
};

#endif // YESNODIALOG_H
