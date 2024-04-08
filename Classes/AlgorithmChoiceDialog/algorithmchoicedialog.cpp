#include "algorithmchoicedialog.h"
#include "Classes/AlgorithmChoiceDialog/ui_algorithmchoicedialog.h"
#include "qpushbutton.h"

AlgorithmChoiceDialog::AlgorithmChoiceDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AlgorithmChoiceDialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Yes)->setText("AStar");
    ui->buttonBox->button(QDialogButtonBox::No)->setText("BFS");
}

AlgorithmChoiceDialog::~AlgorithmChoiceDialog()
{
    delete ui;
}
