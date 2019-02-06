#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ni = new NumericalIntegration("sadfca");

    runButton = ui->RunButton;
    resetButton = ui->ResetButton;

    chartView = ui->ChartView;
    chartView->setRenderHint(QPainter::Antialiasing);

    setWindowTitle(QCoreApplication::applicationName());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRunButtonPressed()
{
    // todo move ni to main.cpp
    QString expression;
    expression = inputText->toPlainText();
    std::string stdstring = expression.toUtf8().constData();
    ni->setExpression(stdstring);
    //ni->parseExpression();
    ni->computeGraphs(true, true, true, false);

    chartView->setChart(ni->getChart());
}

void MainWindow::onResetButtonPressed()
{

}
