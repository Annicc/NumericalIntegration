#include "numericalintegration.h"

NumericalIntegration::NumericalIntegration() {
    chart = new QChart();
}// NumericalIntegration

void NumericalIntegration::computeGraphs(bool expression, bool rettangoli, bool trapezoidi, bool Simpson) {
    if(expression) graphExpression();
    if(rettangoli) graphRettangoli();
    if(trapezoidi) graphTrapezoidi();
    if(Simpson) graphSimpson();
}// computeGraphs

void NumericalIntegration::graphExpression() {
    expression->setX(from);
    QSplineSeries *graph = new QSplineSeries();
    graph->setName("Funzione");
    for (int i = 0; i < gresolution; i++) {
        *graph << QPointF(expression->getX(), expression->getY());
        expression->addX(gdelta);
    }
    chart->addSeries(graph);
}// graphExpression

void NumericalIntegration::graphRettangoli() {
    expression->setX(from);
    QLineSeries *rect = new QLineSeries();
    rect->setName("Rettangoli");
    for (int i = 0; i < resolution; ++i) {
        double y = expression->getY();
        out += expression->getY() * delta;
        *rect << QPointF(expression->getX(), y) << QPointF(expression->getX()+delta, y);
        expression->addX(delta);
    }
    chart->addSeries(rect);
}// graphRettangoli

void NumericalIntegration::graphTrapezoidi() {
    out = 0;
    expression->setX(from);
    QLineSeries *trap = new QLineSeries();
    trap->setName("Trapezi");
    for (int i = 0; i < resolution; ++i) {
        double y1 = expression->getY();
        expression->addX(delta);
        double y2 = expression->getY();
        out += (y1+y2)*delta/2;
        *trap << QPointF(expression->getX()-delta, y1) << QPointF(expression->getX(), y2);
    }
    chart->addSeries(trap);
}// graphTrapezoidi

void NumericalIntegration::graphSimpson() {
    out = 0;
    for (int i = 1; i <= resolution/2; ++i) {
        expression->setX(from + (2 * i - 2) * delta);
        out += expression->getY();
        expression->setX(from + (2 * i - 1) * delta);
        out += 4*expression->getY();
        expression->setX(from + 2 * i * delta);
        out += expression->getY();
    }

    out *= delta/3;
}// graphSimpson

QChart* NumericalIntegration::getChart() {
    chart->createDefaultAxes();
    chart->setTitle(QString::fromStdString(expression_string));
    return chart;
}// getChart


void NumericalIntegration::setExpression(std::string in) {
    expression_string = in;
}// setExpression

void NumericalIntegration::setInterval(int from, int to) {
    this->from = from;
    this->to = to;
}// setInterval

void NumericalIntegration::setResolution(int res){
    resolution = res;
}// setResolution

void NumericalIntegration::setGResolution(int gres){
    gresolution = gres;
}// setGResolution

void NumericalIntegration::buildExpression() {
    delta = (to-from)/resolution;
    gdelta = (to-from)/gresolution;
    out = 0;

    expression = new Expression(expression_string);

}// buildExpression

std::string NumericalIntegration::getExpression(){
    return expression_string;
}// getExpression

double NumericalIntegration::getFrom(){
    return from;
}// getFrom

double NumericalIntegration::getTo(){
    return to;
}// getTo

double NumericalIntegration::getOut(){
    return out;
}// getOut
