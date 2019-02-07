#include "expression.h"

Expression::Expression(std::string expression_string) {
    symbol_table.add_variable("x",x);
    symbol_table.add_constants();
    expression.register_symbol_table(symbol_table);
    parser.compile(expression_string,expression);
}

void Expression::setX(double value) {
    x = value;
}

void Expression::addX(double value) {
    x += value;
}

double Expression::getX() {
    return x;
}

double Expression::getY() {
    return expression.value();
}
