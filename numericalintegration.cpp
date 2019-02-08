#include "numericalintegration.h"

NumericalIntegration::NumericalIntegration() {
    chart = new QChart();
}// NumericalIntegration

void NumericalIntegration::computeGraphs(bool expression, bool rettangoli, bool trapezoidi, bool Simpson) {
    if(expression) graphExpression();
    if(rettangoli) graphRectangle();
    if(trapezoidi) graphTrapezoidal();
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

void NumericalIntegration::graphRectangle() {
    NIResult result = NIMethods::rectangle(expression, from, to, resolution);
    rectangleOut = result.first;
    QLineSeries *qline = new QLineSeries;
    qline->setName("Rettangoli");
    for (auto e : result.second) *qline << QPointF(e.first, e.second);
    chart->addSeries(qline);
}// graphRectangle

void NumericalIntegration::graphTrapezoidal() {
    NIResult result = NIMethods::trapezoidal(expression, from, to, resolution);
    trapezoidalOut = result.first;
    QLineSeries *qline = new QLineSeries;
    qline->setName("Trapezi");
    for (auto e : result.second) *qline << QPointF(e.first, e.second);
    chart->addSeries(qline);
}// graphTrapezoidal

void NumericalIntegration::graphSimpson() {
    NIResult result = NIMethods::simpson(expression, from, to, resolution);
    simpsonOut = result.first;
}// graphSimpson

QChart* NumericalIntegration::getChart() {
    chart->createDefaultAxes();
    chart->setTitle(QString::fromStdString(expression_string));
    return chart;
}// getChart


void NumericalIntegration::setExpression(std::string in) {
    expression_string = in;
}// setExpression

void NumericalIntegration::setInterval(double from, double to) {
    this->from = from;
    this->to = to;
}// setInterval

void NumericalIntegration::setResolution(unsigned int res){
    resolution = res;
}// setResolution

void NumericalIntegration::setGResolution(int gres){
    gresolution = gres;
}// setGResolution

void NumericalIntegration::buildExpression() {
    delta = (to-from)/resolution;
    gdelta = (to-from)/gresolution;

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

double NumericalIntegration::getRectangleOut(){
    return rectangleOut;
}// getRectangleOut

double NumericalIntegration::getTrapezoidalOut(){
    return trapezoidalOut;
}// getTrapezoidalOut

double NumericalIntegration::getSimpsonOut(){
    return simpsonOut;
}// getSimpsonOut
