#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "AddItemDialog.h"
#include "dataio.h"
#include <QCloseEvent>
#include <QWidget>
#include <qmainwindow.h>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void AddItem(AddItemDialog &dialog, bool isEdit);
    void setBookItem(int rowIndex, Book_1 &book);
    void setCDItem(int rowIndex, VideoCD_2 &cd);
    void setPicItem(int rowIndex, Picture_2 &pic);

    void setTableItems();

  private:
    Ui::MainWindow *ui;
    DatabaseHandler *handler;
    Utils utils;
    bool isSaveNeeded = false;

  protected:
    void closeEvent(QCloseEvent *event) override;

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

#endif // MAINWINDOW_H
