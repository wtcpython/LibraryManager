#include "DeleteDialog.h"
#include "valid.h"
#include <QIntValidator>

DeleteDialog::DeleteDialog(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::DeleteDialogClass())
{
	ui->setupUi(this);

	setWindowTitle("删除物品");
	setWindowIcon(QIcon("://res/icon.ico"));

	QIntValidator* intValidator = new QIntValidator(1, 20, this);
	ui->idLine->setValidator(intValidator);

	ui->validText->setStyleSheet("QLabel { color : red; }");
}

DeleteDialog::~DeleteDialog()
{
	delete ui;
}

void DeleteDialog::on_idLine_textChanged(QString text)
{
	QString info = "ID 不符合要求";
	if (!isValidId(text.toStdString()))
	{
		if (ui->validText->text() != info)
			ui->validText->setText(info);
	}
	else
	{
		ui->validText->setText("");
	}
}

void DeleteDialog::on_exitButton_clicked()
{
	id = ui->idLine->text().toInt();
	this->close();
}

int DeleteDialog::getId()
{
	return id;
}