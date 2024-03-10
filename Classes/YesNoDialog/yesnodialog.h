#ifndef YESNODIALOG_H
#define YESNODIALOG_H

#include <QDialog>

namespace Ui {
class YesNoDialog;
}

class YesNoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit YesNoDialog(QWidget *parent = nullptr);
    ~YesNoDialog();

private:
    Ui::YesNoDialog *ui;
};

#endif // YESNODIALOG_H
