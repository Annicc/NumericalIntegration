#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ni = new NumericalIntegration();

    runButton = ui->runButton;
    resetButton = ui->resetButton;
    aboutButton = ui->aboutButton;

    inputExpression = ui->expressionInput;
    upperLimit = ui->upperLimitInput;
    lowerLimit = ui->lowerLimitInput;

    resultDisplay = ui->resultView;
    resultDisplay->setPlainText(resultBuilder("", "", "", ""));

    cbExpression = ui->checkExpression;
    cbRettangoli = ui->checkRettangoli;
    cbTrapezoidi = ui->checkTrapezoidi;
    cbSimpson = ui->checkSimpson;

    resolution = ui->resInput;
    gresolution = ui->gresInput;

    connect(runButton, SIGNAL(clicked()), this, SLOT(onRunButtonPressed()));
    connect(resetButton, SIGNAL(clicked()), this,SLOT(onResetButtonPressed()));
    connect(aboutButton, SIGNAL(clicked()), this,SLOT(onAboutButtonPressed()));

    chartView = ui->chartView;
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setRubberBand(QChartView::RectangleRubberBand);

    setWindowTitle(QCoreApplication::applicationName());
}// MainWindow

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setNi(NumericalIntegration* input){
    ni = input;
}// ~MainWindow

void MainWindow::onRunButtonPressed() {

    // checking user input
    if(!isUserInputCorrect()){
        QMessageBox msgBox;
        msgBox.setText("The inputted data is not correct.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    } else {
        chartView->chart()->removeAllSeries(); // remove old chart

        QString expression;
        expression = inputExpression->text();
        std::string stdstring = expression.toUtf8().constData();
        ni->setExpression(stdstring);
        ni->setInterval(lowerLimit->text().toInt(), upperLimit->text().toInt());
        ni->setResolution(resolution->text().toInt());
        ni->setGResolution(gresolution->text().toInt());

        ni->buildExpression();
        ni->computeGraphs(cbExpression->isChecked(), cbRettangoli->isChecked(), cbTrapezoidi->isChecked(), cbSimpson->isChecked());

        chartView->setChart(ni->getChart()); // add new chart
        chartView->update();

        resultDisplay->setPlainText(resultBuilder(
                                        QString::fromStdString(ni->getExpression()),
                                        QString::number(ni->getFrom()),
                                        QString::number(ni->getTo()),
                                        QString::number(ni->getOut())));

        //resize to content
    }
}// onRunButtonPressed

void MainWindow::onResetButtonPressed() {

    QMessageBox msgBox;
    msgBox.setText("Do you want to reset?");
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();

    if(ret == QMessageBox::Yes){
        inputExpression->clear();
        upperLimit->clear();
        lowerLimit->clear();
        chartView->chart()->removeAllSeries();
        chartView->update();
        resultDisplay->setPlainText(resultBuilder("", "", "", ""));
    }
}// onResetButtonPressed

void MainWindow::onAboutButtonPressed(){
    QMessageBox msgBox;
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText("<p>Authors:<br>"
                   "    Luca Annicchiarico<br>"
                   "    Marco Fincato<br></p>"
                   "<p><a href=https://github.com/marc0777/NumericalIntegration>Github</a><br>"
                   "©Copyright 2019 </p>");
    msgBox.addButton(tr("Nice"), QMessageBox::AcceptRole);
    msgBox.exec();
}// onAboutButtonPressed

bool MainWindow::isUserInputCorrect(){
    return
        !inputExpression->text().isEmpty() || // doesn't work on second run
        !lowerLimit->text().isEmpty() ||
        !upperLimit->text().isEmpty();
}// isUserInputCorrect

QString MainWindow::resultBuilder(QString expression, QString from, QString to, QString result){
    QString str;
    str.append("expression: " + expression + "\n");
    str.append("from: " + from + "\n");
    str.append("to: " + to + "\n");
    str.append("result: " + result);
    return str;
}// resultBuilder
