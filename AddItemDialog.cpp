#include "AddItemDialog.h"
#include "valid.h"

AddItemDialog::AddItemDialog(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::AddItemDialogClass())
{
	ui->setupUi(this);

	setWindowIcon(QIcon("://res/icon.ico"));

	QStringList gradeList;
	gradeList << "未评级" << "一般" << "成人" << "儿童";
	ui->gradeBox->addItems(gradeList);

	QStringList mediaTypeList;
	mediaTypeList << "图书" << "视频光盘" << "图画";
	ui->mediaTypeBox->addItems(mediaTypeList);

	QIntValidator* intValidator = new QIntValidator(1, INT_MAX, this);
	ui->pageLine->setValidator(intValidator);
	ui->yearLine->setValidator(intValidator);
	ui->videoLengthLine->setValidator(intValidator);
	ui->widthLine->setValidator(intValidator);
	ui->lengthLine->setValidator(intValidator);
	ui->idLine->setValidator(intValidator);

	ui->validText->setStyleSheet("QLabel { color : red; }");
}

AddItemDialog::~AddItemDialog()
{
	delete ui;
}

Book_1 AddItemDialog::getBook()
{
	return book;
}

VideoCD_2 AddItemDialog::getCD()
{
	return cd;
}

Picture_2 AddItemDialog::getPic()
{
	return pic;
}

void AddItemDialog::saveItem(int index, bool isTemplate)
{
	int id = ui->idLine->text().toInt();
	QString title = ui->titleLine->text();
	QString author = ui->authorLine->text();
	QString grade = ui->gradeBox->currentText();
	QString press = ui->pressLine->text();
	QString isbn = ui->isbnLine->text();
	int page = ui->pageLine->text().toInt();
	QString name = ui->nameLine->text();
	int year = ui->yearLine->text().toInt();
	int videoLength = ui->videoLengthLine->text().toInt();
	QString country = ui->countryLine->text();
	int width = ui->widthLine->text().toInt();
	int length = ui->lengthLine->text().toInt();

	if (index == 0)
	{
		book = Book_1(id, title, author, grade, press, isbn, page);
	}

	else if (index == 1)
	{
		cd = VideoCD_2(id, title, author, grade, name, year, videoLength);
	}

	else if (index == 2)
	{
		pic = Picture_2(id, title, author, grade, country, length, width);
	}
}

void AddItemDialog::on_mediaTypeBox_currentIndexChanged(int index)
{
	if (lastIndex != index)
	{
		saveItem(lastIndex, true);
		lastIndex = index;
	}
	setItem(index);

	for (int i = 10; i < 28; i++)
	{
		ui->formLayout->itemAt(i)->widget()->setVisible(false);
	}

	if (index == 0)
	{
		for (int i = 10; i < 16; i++)
		{
			ui->formLayout->itemAt(i)->widget()->setVisible(true);
		}
	}

	else if (index == 1)
	{
		for (int i = 16; i < 22; i++)
		{
			ui->formLayout->itemAt(i)->widget()->setVisible(true);
		}
	}

	else if (index == 2)
	{
		for (int i = 22; i < 28; i++)
		{
			ui->formLayout->itemAt(i)->widget()->setVisible(true);
		}
	}
}

void AddItemDialog::on_exitButton_clicked()
{
	if (inValidList.isEmpty())
	{
		int index = ui->mediaTypeBox->currentIndex();
		saveItem(index, false);

		this->close();
	}
}

void AddItemDialog::setItem(int index)
{
	if (index == 0)
	{
		ui->idLine->setText(QString::number(book.getId()));
		ui->titleLine->setText(book.getTitle());
		ui->authorLine->setText(book.getAuthor());
		ui->gradeBox->setCurrentText(book.getGrade());
		ui->pressLine->setText(book.getPublishingHouse());
		ui->isbnLine->setText(book.getIsbn());
		ui->pageLine->setText(QString::number(book.getPage()));
	}
	else if (index == 1)
	{
		ui->idLine->setText(QString::number(cd.getId()));
		ui->titleLine->setText(cd.getTitle());
		ui->authorLine->setText(cd.getAuthor());
		ui->gradeBox->setCurrentText(cd.getGrade());
		ui->nameLine->setText(cd.getName());
		ui->yearLine->setText(QString::number(cd.getProductionYear()));
		ui->videoLengthLine->setText(QString::number(cd.getVideoDuration()));
	}
	else if (index == 2)
	{
		ui->idLine->setText(QString::number(pic.getId()));
		ui->titleLine->setText(pic.getTitle());
		ui->authorLine->setText(pic.getAuthor());
		ui->gradeBox->setCurrentText(pic.getGrade());
		ui->countryLine->setText(pic.getProductionNationality());
		ui->widthLine->setText(QString::number(pic.getWidth()));
		ui->lengthLine->setText(QString::number(pic.getLength()));
	}
}

void AddItemDialog::setMotiflyItem(Utils& utils)
{
	this->book = utils.getLastbook();
	this->cd = utils.getLastcd();
	this->pic = utils.getLastpic();
	setItem(ui->gradeBox->currentIndex());
}

void AddItemDialog::on_idLine_textChanged(QString text)
{
	QString info = "ID 不符合要求";
	if (!isValidId(text.toStdString()))
	{
		if (!inValidList.contains(info))
			inValidList.append(info);
	}
	else
	{
		inValidList.removeAll(info);
	}
	ui->validText->setText(inValidList.join("\n"));
}

void AddItemDialog::on_isbnLine_textChanged(QString text)
{
	QString info = "ISBN 不符合规范";
	if (!isValidISBN(text.toStdString()))
	{
		if (!inValidList.contains(info))
			inValidList.append(info);
	}
	else
	{
		inValidList.removeAll(info);
	}
	ui->validText->setText(inValidList.join("\n"));
}

void AddItemDialog::setMediaIndex(int index)
{
	ui->mediaTypeBox->setCurrentIndex(index);
}