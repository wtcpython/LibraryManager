#include "LibraryManager.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LibraryManager w;
    w.show();
    return a.exec();
}
