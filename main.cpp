#include <QApplication>
#include "mainwindow.h"

const QString ApplicationTitle = "Numerical Integration";

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName(ApplicationTitle);;

    NumericalIntegration *ni = new NumericalIntegration();

    MainWindow w;
    w.setNi(ni);
    w.show();

    return a.exec();
}// main
