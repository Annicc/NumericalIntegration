#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include "numericalintegration.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onRunButtonPressed();
    void onResetButtonPressed();
    void onAboutButtonPressed();
private:
    /**
     * Checks whether the input is correct
     * @return true is the input is correct
     */
    bool isUserInputCorrect();
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

    QChartView *chartView;
    QPushButton *runButton;
    QPushButton *resetButton;

    QPushButton *aboutButton;

};

#endif // MAINWINDOW_H
