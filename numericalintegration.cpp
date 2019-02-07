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
    x = from;
    QSplineSeries *graph = new QSplineSeries();
    graph->setName("Funzione");
    for (int i = 0; i < gresolution; i++) {
        *graph << QPointF(x, expression.value());
        x+=gdelta;
    }
    chart->addSeries(graph);
}// graphExpression

void NumericalIntegration::graphRettangoli() {
    x = from;
    QLineSeries *rect = new QLineSeries();
    rect->setName("Rettangoli");
    for (int i = 0; i < resolution; ++i) {
        double y = expression.value();
        out += expression.value() * delta;
        *rect << QPointF(x, y) << QPointF(x+delta, y);
        x += delta;
    }
    chart->addSeries(rect);
}// graphRettangoli

void NumericalIntegration::graphTrapezoidi() {
    out = 0;
    x = from;
    QLineSeries *trap = new QLineSeries();
    trap->setName("Trapezioidi");
    for (int i = 0; i < resolution; ++i) {
        double y1 = expression.value();
        x += delta;
        double y2 = expression.value();
        out += (y1+y2)*delta/2;
        *trap << QPointF(x-delta, y1) << QPointF(x, y2);
    }
    chart->addSeries(trap);
}// graphTrapezoidi

void NumericalIntegration::graphSimpson() {
    out = 0;
    for (int i = 1; i <= resolution/2; ++i) {
        x = from + (2 * i - 2) * delta;
        out += expression.value();
        x = from + (2 * i - 1) * delta;
        out += 4*expression.value();
        x = from + 2 * i * delta;
        out += expression.value();
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

void NumericalIntegration::buildExpression() {
    resolution = 10;
    gresolution = 100;
    delta = (to-from)/resolution;
    gdelta = (to-from)/gresolution;
    out = 0;

    symbol_table.add_variable("x",x);
    symbol_table.add_constants();
    expression.register_symbol_table(symbol_table);
    parser.compile(expression_string,expression);
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
