#include <iostream>
#include "exprtk.hpp"

using namespace std;

typedef exprtk::symbol_table<double> Symbols;
typedef exprtk::expression<double> Expression;
typedef exprtk::parser<double> Parser;

void compute() {
    string expression_string = "x^2+6x";
    double x;

    Symbols symbol_table;
    symbol_table.add_variable("x",x);
    symbol_table.add_constants();

    Expression expression;
    expression.register_symbol_table(symbol_table);

    Parser parser;
    parser.compile(expression_string,expression);

    double from = 0;
    double to = 2;
    double resolution = 500;
    double delta = (to-from)/resolution;
    double out = 0;

    for (x = from; x <= to-delta; x += delta) {
        out += expression.value()*delta;
    }

    cout << "Result A: " << out << endl;

    out = 0;

    for (x = from; x <= to-delta; ) {
        double temp = expression.value();
        x += delta;
        out += (temp+expression.value())*delta/2;
    }

    cout << "Result B: " << out << endl;
}

int main() {
    compute();
    return 0;
}

