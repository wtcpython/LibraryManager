#pragma once

#include "AddItemDialog.h"
#include "dataio.h"
#include "ui_LibraryManager.h"
#include "utils.h"
#include <QtWidgets/QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class LibraryManagerClass; };
QT_END_NAMESPACE

class LibraryManager : public QMainWindow
{
	Q_OBJECT

public:
	LibraryManager(QWidget* parent = nullptr);
	~LibraryManager();
	void AddItem(AddItemDialog& dialog);
	void setBookItem(int rowIndex, Book_1& book);
	void setCDItem(int rowIndex, VideoCD_2& cd);
	void setPicItem(int rowIndex, Picture_2& pic);

	void setTableItems();

private:
	Ui::LibraryManagerClass* ui;
	DatabaseHandler* handler;
	Utils utils;
	bool isSaveNeeded = false;

protected:
	void closeEvent(QCloseEvent* event) override;

private slots:
	void on_actionExit_triggered();
	void on_actionOpenFile_triggered();
	void on_actionSaveFile_triggered();
	void on_actionAbout_this_Application_triggered();
	void on_actionAbout_Qt_triggered();

	void on_mediaTypeBox_currentIndexChanged(int index);

	void on_addItemButton_clicked();
	void on_editItemButton_clicked();
	void on_deleteItemButton_clicked();
	void on_searchItemButton_clicked();
	void on_statisticButton_clicked();
};
