#include "mainwindow.h"

#include <QApplication>
#include <QDir>
#include <iostream>
int main(int argc, char *argv[])
{
//    QDir::setSearchPaths("images", QStringList(QDir::currentPath() + "/qt/images"));
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Парсер функции вывода printf");
    w.show();
    return a.exec();
}
