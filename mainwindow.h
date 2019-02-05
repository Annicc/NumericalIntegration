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
    void onRunButtonPressed();
    void onResetButtonPressed();
private:
    Ui::MainWindow *ui;
    NumericalIntegration *ni;
    QTextEdit *inputText;
    QChartView *chartView;
    QPushButton *runButton;
    QPushButton *resetButton;
};

#endif // MAINWINDOW_H
