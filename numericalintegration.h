#ifndef NUMERICALINTEGRATION_H
#define NUMERICALINTEGRATION_H

#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>

#include "exprtk.hpp"
#include <iomanip>

typedef exprtk::symbol_table<double> Symbols;
typedef exprtk::expression<double> Expression;
typedef exprtk::parser<double> Parser;

class NumericalIntegration
{
public:
    NumericalIntegration();
    void parseExpression();

    /*
     * This function uses the graphSomething functions
     * @param using graphExpression
     * @param using graphRettangoli
     * @param using graphTrapezoidi
     * @param using graphSimpson
     */
    void computeGraphs(bool expression, bool rettangoli, bool trapezoidi, bool Simpson);

    QChart getChart(); // must use computeGraphs first
    void setExpression(Expression in);

private:
    void graphExpression();
    void graphRettangoli();
    void graphTrapezoidi();
    void graphSimpson();

    QChart *chart;
    double from, to, x, delta, gdelta, gresolution, out;
    int resolution;
    std::string expression_string;
    Symbols symbol_table;
    Expression expression;
    Parser parser;
};

#endif // NUMERICALINTEGRATION_H
