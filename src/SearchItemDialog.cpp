#include "SearchItemDialog.h"
#include "ui_SearchItemDialog.h"
#include <QIntValidator>

SearchItemDialog::SearchItemDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SearchItemDialogClass())
{
    ui->setupUi(this);

    setWindowTitle("查询物品");
    setWindowIcon(QIcon("res/icon.ico"));

    ui->verticalLayout->setAlignment(Qt::AlignTop);

    ui->noButton->setChecked(true);

    QIntValidator *intValidator = new QIntValidator(this);
    ui->idLine->setValidator(intValidator);
}

SearchItemDialog::~SearchItemDialog()
{
    delete ui;
}

void SearchItemDialog::on_exitButton_clicked()
{
    if (ui->idButton->isChecked())
    {
        this->id = ui->idLine->text().toInt();
    }
    else if (ui->titleButton->isChecked())
    {
        this->title = ui->titleLine->text();
    }
    this->close();
}

int SearchItemDialog::getId()
{
    return id;
}

QString SearchItemDialog::getTitle()
{
    return title;
}