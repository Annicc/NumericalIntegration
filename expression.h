#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "exprtk.hpp"

#include <QString>

using namespace exprtk;

class Expression {
public:
    Expression(std::string expression);
    void setX(double value);
    void addX(double value);
    double getX();
    double getY();
private:
    double x;
    symbol_table<double> symbol_table;
    expression<double> expression;
    parser<double> parser;
};

#endif // EXPRESSION_H
