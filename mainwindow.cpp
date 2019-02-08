#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ni = new NumericalIntegration();

    runButton = ui->runButton;
    resetButton = ui->resetButton;
    aboutButton = ui->aboutButton;
    theCancelButton = ui->theCancelButton;

    inputExpression = ui->expressionInput;
    upperLimit = ui->upperLimitInput;
    lowerLimit = ui->lowerLimitInput;

    resExpression = ui->resExpression;
    resFrom = ui->resFrom;
    resTo = ui->resTo;
    resRectangle = ui->resRectangle;
    resTrapezoidal = ui->resTrapezoidal;
    resSimspon = ui->resSimpson;

    cbExpression = ui->checkExpression;
    cbRettangoli = ui->checkRettangoli;
    cbTrapezoidi = ui->checkTrapezoidi;
    cbSimpson = ui->checkSimpson;

    resolution = ui->resInput;
    gresolution = ui->gresInput;

    connect(runButton, SIGNAL(clicked()), this, SLOT(onRunButtonPressed()));
    connect(resetButton, SIGNAL(clicked()), this,SLOT(onResetButtonPressed()));
    connect(aboutButton, SIGNAL(clicked()), this,SLOT(onAboutButtonPressed()));
    connect(theCancelButton, SIGNAL(clicked()), this,SLOT(onTheCancelButtonPressed()));

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
        ni->setInterval(lowerLimit->value(), upperLimit->value());
        ni->setResolution(resolution->value());
        ni->setGResolution(gresolution->value());

        ni->buildExpression();
        ni->computeGraphs(cbExpression->isChecked(), cbRettangoli->isChecked(), cbTrapezoidi->isChecked(), cbSimpson->isChecked());

        chartView->setChart(ni->getChart()); // add new chart
        chartView->update();

        buildResult();
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
        resExpression->clear();
        resFrom->clear();
        resTo->clear();
        resRectangle->clear();
        resTrapezoidal->clear();
        resSimspon->clear();
        chartView->chart()->removeAllSeries();
        chartView->update();
    }
}// onResetButtonPressed

void MainWindow::onAboutButtonPressed(){
    QMessageBox msgBox;
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText("Authors:<br>"
                   "<a href=https://github.com/annicc>Luca Annicchiarico</a><br>"
                   "<a href=https://github.com/marc0777>Marco Fincato</a><br>"
                   "<br>"
                   "<a href=https://github.com/marc0777/NumericalIntegration>Github</a><br>"
                   "©Copyright 2019");
    msgBox.setTextInteractionFlags(Qt::NoTextInteraction);
    msgBox.addButton(tr("Nice"), QMessageBox::AcceptRole);
    msgBox.exec();
}// onAboutButtonPressed

void MainWindow::onTheCancelButtonPressed(){
    QMessageBox msgBox;
    msgBox.setText("Are you sure you want to C̵̤̭̭̙̪̟͕͓̱̮͝ ̶̢̬̞̬͓͓̪̲̹̫͗̎̿͝ ̶̡̟̘͚͈̐͘ͅȂ̷̛̩̣̬̫̣͈̥̖͂͋̊̊̀̈̀̌ ̶͔͎̥͚̱̘̫̮͙̅̿̑̀̚͝ ̸̥͔̮̘̦͕̟̥̙̈́̒̊͂̽͜N̵͔͉͂̏ ̴̝̝͙̌̀̽̌̒͝ ̵̹̒̇̀̓̓̄͒̇̉̾C̸̢̾̈́̈́̽͆ ̴̱̘͇̮͆̈́̃͌͆͐̇͠ ̶̞̖̉̈͒͂͗̃͒̾̿͝E̵̡͚͍̗͌͊̈͘̚ ̷̪̘̤͚̇̉̐̽͋͊̐͋ ̸̲͕̮͔̤̮̪̥͌̐̚̕͘͜͝L̵̼̣̬̟͎͈̥͚̹̋̚͝ͅ ?");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::No);
    msgBox.addButton(tr("please have mercy"), QMessageBox::DestructiveRole);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();

    QMessageBox msgCancel;
    QMessageBox msgPlease;
    switch (ret) {
        case QMessageBox::Cancel:
            msgCancel.setText("You have successfully cancelled");
            msgCancel.setStandardButtons(QMessageBox::Ok);
            msgCancel.exec();
        break;
        case QMessageBox::No:
            onTheCancelButtonPressed();
        break;
        default:
            msgPlease.setText("I will 🆂  🅿  🅰  🆁  🅴 you");
            msgPlease.addButton(tr("thank you master"), QMessageBox::AcceptRole);
            msgPlease.exec();
        break;
    }
}// onTheCancelButtonPressed

bool MainWindow::isUserInputCorrect(){
    return
        !inputExpression->text().isEmpty() || // doesn't work on second run
        !lowerLimit->text().isEmpty() ||
        !upperLimit->text().isEmpty();
}// isUserInputCorrect

void MainWindow::buildResult(){
    resExpression->setText(QString::fromStdString(ni->getExpression()));
    resFrom->setText(QString::number(ni->getFrom()));
    resTo->setText(QString::number(ni->getTo()));


    resRectangle->setText(QString::number(ni->getRectangleOut()));
    resTrapezoidal->setText(QString::number(ni->getTrapezoidalOut()));
    resSimspon->setText(QString::number(ni->getSimpsonOut()));
}// resultBuilder
