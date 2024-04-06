#include "yesnodialog.h"
#include "Classes/YesNoDialog/ui_yesnodialog.h"
#include "qpushbutton.h"

YesNoDialog::YesNoDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::YesNoDialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Yes)->setText("Tak");
    ui->buttonBox->button(QDialogButtonBox::No)->setText("Nie");
}

YesNoDialog::~YesNoDialog()
{
    delete ui;
}
