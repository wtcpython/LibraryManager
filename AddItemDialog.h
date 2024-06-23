#pragma once

#include "book.h"
#include "Picture.h"
#include "ui_AddItemDialog.h"
#include "utils.h"
#include "VideoCD.h"
#include <QDialog>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui { class AddItemDialogClass; };
QT_END_NAMESPACE

class AddItemDialog : public QDialog
{
	Q_OBJECT

public:
	AddItemDialog(QWidget* parent = nullptr);
	~AddItemDialog();
	void setMotiflyItem(Utils& utils);

	Book_1 getBook();
	VideoCD_2 getCD();
	Picture_2 getPic();

private:
	Ui::AddItemDialogClass* ui;
	Book_1 book;
	VideoCD_2 cd;
	Picture_2 pic;
	int lastIndex = 0;

	void saveItem(int index, bool isTemplate);
	void setItem(int index);
	QStringList inValidList;

private slots:
	void on_mediaTypeBox_currentIndexChanged(int index);
	void on_exitButton_clicked();
	void on_idLine_textChanged(QString text);
	void on_isbnLine_textChanged(QString text);
};
