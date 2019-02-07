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

    /**
     * Creates a string with all the input and output of the mathematical operations.
     * @param expression base mathematical expression
     * @param from integral lower limit
     * @param to integral higher limit
     * @param result definite result of the integral
     * @return a string with a lot of "\n"
     */
    QString resultBuilder(QString expression, QString from, QString to, QString result);

    Ui::MainWindow *ui;
    NumericalIntegration *ni;

    QLineEdit *inputExpression;
    QLineEdit *upperLimit;
    QLineEdit *lowerLimit;

    QTextEdit *resultDisplay;

    QCheckBox *cbExpression;
    QCheckBox *cbRettangoli;
    QCheckBox *cbTrapezoidi;
    QCheckBox *cbSimpson;

    QLineEdit *resolution;
    QLineEdit *gresolution;

    QChartView *chartView;
    QPushButton *runButton;
    QPushButton *resetButton;

    QPushButton *aboutButton;
    QPushButton *theCancelButton; // easter egg time :-)
};

#endif // MAINWINDOW_H
