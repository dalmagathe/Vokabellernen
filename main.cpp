#include "Headers/mainwindow.h"
#include "iostream"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    if (w.isActiveWindow())
    {
        w.openDB();
    }
    return a.exec();

}
