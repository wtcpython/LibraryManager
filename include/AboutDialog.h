#pragma once

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class AboutDialogClass; };
QT_END_NAMESPACE

class AboutDialog : public QDialog
{
	Q_OBJECT

public:
	AboutDialog(QWidget* parent = nullptr);
	~AboutDialog();

private:
	Ui::AboutDialogClass* ui;
private slots:
	void on_exitButton_clicked();
};
