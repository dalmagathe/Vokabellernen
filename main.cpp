#include "mainwindow.h"
#include "iostream"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    if (w.isActiveWindow())
    {
        w.openBDD();
    }
    return a.exec();

}
