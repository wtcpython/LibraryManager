#include "DeleteDialog.h"
#include "LibraryManager.h"
#include "SearchItemDialog.h"
#include <AboutDialog.h>
#include <QFileDialog>
#include <QMessageBox>

LibraryManager::LibraryManager(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::LibraryManagerClass())
{
	ui->setupUi(this);
	setWindowIcon(QIcon("://res/icon.ico"));
	handler = new DatabaseHandler();
	ui->tableWidget->setRowCount(20);
	ui->tableWidget->setColumnCount(7);
	ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

	QStringList mediaTypeList;
	mediaTypeList << "图书" << "视频光盘" << "图画";
	ui->mediaTypeBox->addItems(mediaTypeList);

	utils = Utils();
}

LibraryManager::~LibraryManager()
{
	delete ui;
}

void LibraryManager::on_actionExit_triggered()
{
	this->close();
}

void LibraryManager::on_actionAbout_this_Application_triggered()
{
	AboutDialog* dialog = new AboutDialog(this);
	dialog->show();
}

void LibraryManager::on_actionAbout_Qt_triggered()
{
	QMessageBox::aboutQt(this);
}

void LibraryManager::on_actionOpenFile_triggered()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Open Database", QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), "Database Files (*.db *.sqlite)");

	if (fileName.isEmpty())
	{
		return;
	}

	handler->openDatabase(fileName);
	for (Book_1 book : handler->fetchBooksData())
	{
		utils.addBookItem(book);
	}

	for (VideoCD_2 cd : handler->fetchVideoCDData())
	{
		utils.addCDItem(cd);
	}

	for (Picture_2 pic : handler->fetchPictureData())
	{
		utils.addPicItem(pic);
	}

	setTableItems();
}

void LibraryManager::on_actionSaveFile_triggered()
{
	if (handler->getFileName() == nullptr)
	{
		QString fileName = QFileDialog::getSaveFileName(this, "Save Database", QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/data.db", "Database Files (*.db *.sqlite)");

		if (fileName.isEmpty())
		{
			return;
		}

		handler->openDatabase(fileName);
	}
	std::vector<int> numbers(20);
	std::iota(numbers.begin(), numbers.end(), 0);

	auto books = utils.getBooks();
	for (int i = 0; i < books.size(); i++)
	{
		if (books[i].getId() != 0)
		{
			handler->insertBook(books[i]);
			auto new_end = std::remove(numbers.begin(), numbers.end(), books[i].getId());
			numbers.erase(numbers.begin() + i);
		}
	}
	auto cds = utils.getCds();
	for (int i = 0; i < cds.size(); i++)
	{
		if (cds[i].getId() != 0)
		{
			handler->insertCD(cds[i]);
			auto new_end = std::remove(numbers.begin(), numbers.end(), cds[i].getId());
			numbers.erase(numbers.begin() + i);
		}
	}
	auto pics = utils.getPics();
	for (int i = 0; i < pics.size(); i++)
	{
		if (pics[i].getId() != 0)
		{
			handler->insertPic(pics[i]);
			auto new_end = std::remove(numbers.begin(), numbers.end(), pics[i].getId());
			numbers.erase(numbers.begin() + i);
		}
	}

	for (int num : numbers)
	{
		handler->deleteLine(num);
	}
	isSaveNeeded = false;
}

void LibraryManager::on_addItemButton_clicked()
{
	if (utils.isFull())
	{
		QMessageBox::warning(this, QString("LibraryManager"), QString("媒体库已满！"), QMessageBox::Yes);
		return;
	}
	AddItemDialog dialog;
	dialog.setWindowTitle("添加物品");
	dialog.exec();
	AddItem(dialog, false);
}

void LibraryManager::on_editItemButton_clicked()
{
	AddItemDialog dialog;
	dialog.setWindowTitle("编辑物品");
	dialog.setMotiflyItem(utils);
	dialog.exec();
	AddItem(dialog, true);
}

void LibraryManager::AddItem(AddItemDialog& dialog, bool isEdit)
{
	Book_1 book = dialog.getBook();
	VideoCD_2 cd = dialog.getCD();
	Picture_2 pic = dialog.getPic();
	bool isExist = false;
	if (isEdit)
	{
		utils.deleteItem(book.getId());
		utils.deleteItem(cd.getId());
		utils.deleteItem(pic.getId());
	}
	if (book.getId() != 0)
	{
		if (!utils.addBookItem(book))
		{
			isExist = true;
		}
	}

	else if (cd.getId() != 0)
	{
		if (!utils.addCDItem(cd))
		{
			isExist = true;
		}
	}

	else if (pic.getId() != 0)
	{
		if (!utils.addPicItem(pic))
		{
			isExist = true;
		}
	}
	if (isExist)
	{
		QMessageBox::warning(this, QString("LibraryManager"), QString("ID 已经存在！"), QMessageBox::Yes);
	}
	setTableItems();
	isSaveNeeded = true;
}

void LibraryManager::setBookItem(int rowIndex, Book_1& book)
{
	ui->tableWidget->setItem(rowIndex, 0, new QTableWidgetItem(QString::number(book.getId())));
	ui->tableWidget->setItem(rowIndex, 1, new QTableWidgetItem(book.getTitle()));
	ui->tableWidget->setItem(rowIndex, 2, new QTableWidgetItem(book.getAuthor()));
	ui->tableWidget->setItem(rowIndex, 3, new QTableWidgetItem(book.getGrade()));
	ui->tableWidget->setItem(rowIndex, 4, new QTableWidgetItem(book.getPublishingHouse()));
	ui->tableWidget->setItem(rowIndex, 5, new QTableWidgetItem(book.getIsbn()));
	ui->tableWidget->setItem(rowIndex, 6, new QTableWidgetItem(QString::number(book.getPage())));
}

void LibraryManager::setCDItem(int rowIndex, VideoCD_2& cd)
{
	ui->tableWidget->setItem(rowIndex, 0, new QTableWidgetItem(QString::number(cd.getId())));
	ui->tableWidget->setItem(rowIndex, 1, new QTableWidgetItem(cd.getTitle()));
	ui->tableWidget->setItem(rowIndex, 2, new QTableWidgetItem(cd.getAuthor()));
	ui->tableWidget->setItem(rowIndex, 3, new QTableWidgetItem(cd.getGrade()));
	ui->tableWidget->setItem(rowIndex, 4, new QTableWidgetItem(cd.getName()));
	ui->tableWidget->setItem(rowIndex, 5, new QTableWidgetItem(QString::number(cd.getProductionYear())));
	ui->tableWidget->setItem(rowIndex, 6, new QTableWidgetItem(QString::number(cd.getVideoDuration())));
}

void LibraryManager::setPicItem(int rowIndex, Picture_2& pic)
{
	ui->tableWidget->setItem(rowIndex, 0, new QTableWidgetItem(QString::number(pic.getId())));
	ui->tableWidget->setItem(rowIndex, 1, new QTableWidgetItem(pic.getTitle()));
	ui->tableWidget->setItem(rowIndex, 2, new QTableWidgetItem(pic.getAuthor()));
	ui->tableWidget->setItem(rowIndex, 3, new QTableWidgetItem(pic.getGrade()));
	ui->tableWidget->setItem(rowIndex, 4, new QTableWidgetItem(pic.getProductionNationality()));
	ui->tableWidget->setItem(rowIndex, 5, new QTableWidgetItem(QString::number(pic.getLength())));
	ui->tableWidget->setItem(rowIndex, 6, new QTableWidgetItem(QString::number(pic.getWidth())));
}

void LibraryManager::on_searchItemButton_clicked()
{
	SearchItemDialog dialog;
	dialog.exec();
	int id = dialog.getId();
	QString title = dialog.getTitle();
	if (id != 0)
	{
		if (utils.searchBookItem(id))
		{
			Book_1 book = utils.getLastbook();
			setBookItem(id - 1, book);
		}

		else if (utils.searchCDItem(id))
		{
			VideoCD_2 cd = utils.getLastcd();
			setCDItem(id - 1, cd);
		}

		else if (utils.searchPicItem(id))
		{
			Picture_2 pic = utils.getLastpic();
			setPicItem(id - 1, pic);
		}
	}

}

void LibraryManager::setTableItems()
{
	ui->tableWidget->clear();

	int index = ui->mediaTypeBox->currentIndex();
	if (index == 0)
	{
		QStringList headers;
		headers << "ID" << "标题" << "作者" << "评级" << "出版社" << "ISBN" << "页数";
		ui->tableWidget->setHorizontalHeaderLabels(headers);
		for (Book_1 book : utils.getBooks())
		{
			if (book.getId() != 0)
			{
				setBookItem(book.getId() - 1, book);
			}
		}
	}

	else if (index == 1)
	{
		QStringList headers;
		headers << "ID" << "标题" << "作者" << "评级" << "出品者名称" << "出品年份" << "视频时长";
		ui->tableWidget->setHorizontalHeaderLabels(headers);
		for (VideoCD_2 cd : utils.getCds())
		{
			if (cd.getId() != 0)
			{
				setCDItem(cd.getId() - 1, cd);
			}
		}
	}

	else if (index == 2)
	{
		QStringList headers;
		headers << "ID" << "标题" << "作者" << "评级" << "出品国籍" << "长" << "宽";
		ui->tableWidget->setHorizontalHeaderLabels(headers);
		for (Picture_2 pic : utils.getPics())
		{
			if (pic.getId() != 0)
			{
				setPicItem(pic.getId() - 1, pic);
			}
		}
	}
}

void LibraryManager::on_mediaTypeBox_currentIndexChanged(int index)
{
	setTableItems();
}

void LibraryManager::on_deleteItemButton_clicked()
{
	if ((utils.statistic())[0] == 0)
	{
		QMessageBox::warning(this, QString("LibraryManager"), QString("物品库为空！"), QMessageBox::Yes);
	}
	else
	{
		DeleteDialog dialog;
		dialog.exec();
		int id = dialog.getId();
		if (utils.deleteItem(id))
		{
			QMessageBox::warning(this, QString("LibraryManager"), QString("ID：%1 删除成功！").arg(id), QMessageBox::Yes);
		}
		else
		{
			QMessageBox::warning(this, QString("LibraryManager"), QString("ID：%1 不存在！").arg(id), QMessageBox::Yes);
		}
	}
	setTableItems();
}

void LibraryManager::on_statisticButton_clicked()
{
	vector<int> nums = utils.statistic();
	QString info = QString("媒体库总量：%1\n图书总量：%2\n视频光盘总量：%3\n图画总量：%4").arg(nums[0]).arg(nums[1]).arg(nums[2]).arg(nums[3]);
	QMessageBox::information(this, QString("LibraryManager"), info, QMessageBox::Yes);
}

void LibraryManager::closeEvent(QCloseEvent* event)
{
	if (isSaveNeeded)
	{
		auto res = QMessageBox::warning(this, QString("LibraryManager"), QString("数据未保存，是否保存？"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
		if (res == QMessageBox::Yes)
		{
			on_actionSaveFile_triggered();
			event->accept();
		}
		else if (res == QMessageBox::No)
		{
			event->accept();
		}
	}
}