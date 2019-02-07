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

class NumericalIntegration {
public:
    /**
     * @param title chart title
     */
    NumericalIntegration();
    void parseExpression();

    /**
     * This function uses the graphSomething functions
     * @param using graphExpression
     * @param using graphRettangoli
     * @param using graphTrapezoidi
     * @param using graphSimpson
     */
    void computeGraphs(bool expression, bool rettangoli, bool trapezoidi, bool Simpson);

    /**
     * Returns a chart containing the graphs requested in computeGraphs function
     * @returns a QChart chart
     */
    QChart* getChart(); // must use computeGraphs first

    /**
     * Sets the base expression.
     * @param in mathematical expression
     */
    void setExpression(std::string in);

    void setInterval(int from, int to);

    void buildExpression();

    std::string getExpression();
    double getFrom();
    double getTo();
    double getOut(); // lol nice name, temp tho

private:
    /**
     * Creates base expression graph.
     */
    void graphExpression();

    /**
     * Creates graph with rettangoli method.
     */
    void graphRettangoli();

    /**
     * Creates graph with trapezoidi method.
     */
    void graphTrapezoidi();

    /**
     * Creates graph with Simpson method.
     */
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
