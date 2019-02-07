#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ni = new NumericalIntegration("sadfca");

    runButton = ui->runButton;
    resetButton = ui->resetButton;
    aboutButton = ui->aboutButton;

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
    connect(aboutButton, SIGNAL(clicked()), this,SLOT(onAboutButtonPressed()));

    chartView = ui->chartView;
    chartView->setRenderHint(QPainter::Antialiasing);

    setWindowTitle(QCoreApplication::applicationName());
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onRunButtonPressed() {

    // checking user input
    if(!isUserInputCorrect()){
        QMessageBox msgBox;
        msgBox.setText("The inputted data is not correct.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }

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

void MainWindow::onAboutButtonPressed(){

}

bool MainWindow::isUserInputCorrect(){
    // todo finish
    return
        !inputExpression->text().isEmpty() ||
        !lowerLimit->text().isEmpty() ||
        !upperLimit->text().isEmpty() ||
        upperLimit->text().toInt() > lowerLimit->text().toInt();
}

QString MainWindow::resultBuilder(){
    QString result;
    result.append("expression: " + QString::fromStdString(ni->getExpression()) + "\n");
    result.append("from: " + QString::number(ni->getFrom()) + "\n");
    result.append("to: " + QString::number(ni->getTo()) + "\n");
    result.append("result: " + QString::number(ni->getOut()));
    return result;
}
