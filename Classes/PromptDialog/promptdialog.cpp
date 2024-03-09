#include "promptdialog.h"
#include "Classes/PromptDialog/ui_promptdialog.h"
#include "qpushbutton.h"

PromptDialog::PromptDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PromptDialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Yes)->setText("Tak");
    ui->buttonBox->button(QDialogButtonBox::No)->setText("Nie");
}

PromptDialog::~PromptDialog()
{
    delete ui;
}
