#ifndef NUMERICALINTEGRATION_H
#define NUMERICALINTEGRATION_H

#include "expression.h"
#include "nimethods.h"

#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>

#include <iomanip>

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

    void setInterval(double from, double to);

    void setResolution(unsigned int res);

    void setGResolution(int gres);

    void buildExpression();

    std::string getExpression();
    double getFrom();
    double getTo();
    double getRectangleOut();
    double getTrapezoidalOut();
    double getSimpsonOut();

private:
    /**
     * Creates base expression graph.
     */
    void graphExpression();

    /**
     * Creates graph with rettangoli method.
     */
    void graphRectangle();

    /**
     * Creates graph with trapezoidi method.
     */
    void graphTrapezoidal();

    /**
     * Creates graph with Simpson method.
     */
    void graphSimpson();

    QChart *chart;
    double from, to, delta, gdelta, gresolution, rectangleOut, trapezoidalOut, simpsonOut;
    unsigned int resolution;
    std::string expression_string;
    Expression *expression;
};

#endif // NUMERICALINTEGRATION_H
