#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include "numericalintegration.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onRunButtonPressed();
    void onResetButtonPressed();
private:
    Ui::MainWindow *ui;
    NumericalIntegration *ni;

    QTextEdit *inputExpression;
    QTextEdit *upperLimit;
    QTextEdit *lowerLimit;

    QCheckBox *cbExpression;
    QCheckBox *cbRettangoli;
    QCheckBox *cbTrapezoidi;
    QCheckBox *cbSimpson;

    QChartView *chartView;
    QPushButton *runButton;
    QPushButton *resetButton;

};

#endif // MAINWINDOW_H
