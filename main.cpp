#include <QApplication>
#include "mainwindow.h"

const QString ApplicationTitle = "Numerical Integration";

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName(ApplicationTitle);;

    MainWindow w;
    w.show();

    return a.exec();
}
