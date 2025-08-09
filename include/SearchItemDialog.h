#pragma once

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui
{
class SearchItemDialogClass;
};
QT_END_NAMESPACE

class SearchItemDialog : public QDialog
{
    Q_OBJECT

  public:
    SearchItemDialog(QWidget *parent = nullptr);
    ~SearchItemDialog();

    int getId();
    QString getTitle();

  private:
    Ui::SearchItemDialogClass *ui;
    QString title;
    int id = 0;

  private slots:
    void on_exitButton_clicked();
};
