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
    NIResult result = NIMethods::rectangle(expression, from, to, resolution);
    QLineSeries *qline = new QLineSeries;
    qline->setName("Rettangoli");
    for (auto e : result.second) *qline << QPointF(e.first, e.second);
    chart->addSeries(qline);
}// graphRettangoli

void NumericalIntegration::graphTrapezoidi() {
    NIResult result = NIMethods::trapezoidal(expression, from, to, resolution);
    QLineSeries *qline = new QLineSeries;
    qline->setName("Trapezi");
    for (auto e : result.second) *qline << QPointF(e.first, e.second);
    chart->addSeries(qline);
}// graphTrapezoidi

void NumericalIntegration::graphSimpson() {
    NIResult result = NIMethods::simpson(expression, from, to, resolution);
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

void NumericalIntegration::setResolution(unsigned int res){
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
