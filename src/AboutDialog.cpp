#include "AboutDialog.h"
#include "ui_AboutDialog.h"

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AboutDialogClass())
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_exitButton_clicked()
{
    this->close();
}