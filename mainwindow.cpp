#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ni = new NumericalIntegration("sadfca");

    runButton = ui->runButton;
    resetButton = ui->resetButton;

    inputExpression = ui->expressionInput;
    upperLimit = ui->upperLimitInput;
    lowerLimit = ui->lowerLimitInput;

    resultDisplay = ui->resultView;

    cbExpression = ui->checkExpression;
    cbRettangoli = ui->checkRettangoli;
    cbTrapezoidi = ui->checkTrapezoidi;
    cbSimpson = ui->checkSimpson;

    connect(runButton, SIGNAL(clicked()), this, SLOT(onRunButtonPressed()));
    connect(resetButton, SIGNAL(clicked()), this,SLOT(onResetButtonPressed()));

    chartView = ui->chartView;
    chartView->setRenderHint(QPainter::Antialiasing);

    setWindowTitle(QCoreApplication::applicationName());
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onRunButtonPressed() {
    // todo move ni to main.cpp
    QString expression;
    expression = inputExpression->text();
    std::string stdstring = expression.toUtf8().constData();
    ni->setExpression(stdstring);
    ni->setInterval(lowerLimit->text().toInt(), upperLimit->text().toInt());
    ni->buildExpression();
    ni->computeGraphs(cbExpression->isChecked(), cbRettangoli->isChecked(), cbTrapezoidi->isChecked(), cbSimpson->isChecked());

    chartView->chart()->removeAllSeries(); // remove old chart
    chartView->setChart(ni->getChart()); // add new chart
    chartView->update();

    resultDisplay->setPlainText(resultBuilder());

    //resize to content
}

void MainWindow::onResetButtonPressed() {
    inputExpression->clear();
    upperLimit->clear();
    lowerLimit->clear();
    chartView->chart()->removeAllSeries();
    chartView->update();
}

QString MainWindow::resultBuilder(){
    QString result;
    result.append("expression: " + QString::fromStdString(ni->getExpression()) + "\n");
    result.append("from: " + QString::number(ni->getFrom()) + "\n");
    result.append("to: " + QString::number(ni->getTo()) + "\n");
    result.append("result: " + QString::number(ni->getOut()));
    return result;
}
