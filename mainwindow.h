#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include "numericalintegration.h"

#include <iostream>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setNi(NumericalIntegration* input);

private slots:
    void onRunButtonPressed();
    void onResetButtonPressed();
    void onAboutButtonPressed();
    void onTheCancelButtonPressed();

private:

    /**
     * Checks whether the input is correct
     * @return true is the input is correct
     */
    bool isUserInputCorrect();

    void buildResult();

    Ui::MainWindow *ui;
    NumericalIntegration *ni;

    QLineEdit *inputExpression;
    QDoubleSpinBox *upperLimit;
    QDoubleSpinBox *lowerLimit;

    QCheckBox *cbExpression;
    QCheckBox *cbRettangoli;
    QCheckBox *cbTrapezoidi;
    QCheckBox *cbSimpson;

    QLineEdit *resExpression;
    QLineEdit *resFrom;
    QLineEdit *resTo;
    QLineEdit *resRectangle;
    QLineEdit *resTrapezoidal;
    QLineEdit *resSimspon;

    QSpinBox *resolution;
    QSpinBox *gresolution;

    QChartView *chartView;
    QPushButton *runButton;
    QPushButton *resetButton;

    QPushButton *aboutButton;
    QPushButton *theCancelButton; // easter egg time :-)
};

#endif // MAINWINDOW_H
