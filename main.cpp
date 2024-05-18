#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("SQLITE APP"); //задаем свой заголовок окна
    w.show();
    return a.exec();
}
