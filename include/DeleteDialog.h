#pragma once

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui
{
class DeleteDialogClass;
};
QT_END_NAMESPACE

class DeleteDialog : public QDialog
{
    Q_OBJECT

  public:
    DeleteDialog(QWidget *parent = nullptr);
    ~DeleteDialog();
    int getId();

  private:
    Ui::DeleteDialogClass *ui;
    int id = 0;
  private slots:
    void on_idLine_textChanged(QString text);
    void on_exitButton_clicked();
};
