#include <iostream>
#include "exprtk.hpp"

#define RESOLUTION 512

using namespace std;

typedef exprtk::symbol_table<double> Symbols;
typedef exprtk::expression<double> Expression;
typedef exprtk::parser<double> Parser;

void compute() {
    string expression_string = "x + 2";
    double x;

    Symbols symbol_table;
    symbol_table.add_variable("x",x);
    symbol_table.add_constants();

    Expression expression;
    expression.register_symbol_table(symbol_table);

    Parser parser;
    parser.compile(expression_string,expression);

    for (x = double(-5); x <= double(+5); x += double(1)) {
        double y = expression.value();
        cout << "X: " << x << "\tY: " << y << endl;
    }
}

int main() {
    compute();
    return 0;
}

