#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ni = new NumericalIntegration();

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
    //Expression expression = inputText->toPlainText();
    //ni->setExpression(expression);
    // do math
    //chartView->setChart();
}

void MainWindow::onResetButtonPressed()
{

}
