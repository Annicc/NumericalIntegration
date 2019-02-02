#include <iostream>
#include <iomanip>
#include "exprtk.hpp"

using namespace std;

typedef exprtk::symbol_table<double> Symbols;
typedef exprtk::expression<double> Expression;
typedef exprtk::parser<double> Parser;

void compute() {

    double from, to, x;
    int resolution;
    string expression_string;

    cout << setprecision(9) << fixed;

    cout << "Funzione: ";
    cin >> expression_string;
    cout << "Inizio dell'intervallo di derivazione: ";
    cin >> from;
    cout << "Fine dell'intervallo di derivazione: ";
    cin >> to;
    cout << "Risoluzione calcolo dell'integrale: ";
    cin >> resolution;


    Symbols symbol_table;
    symbol_table.add_variable("x",x);
    symbol_table.add_constants();

    Expression expression;
    expression.register_symbol_table(symbol_table);

    Parser parser;
    parser.compile(expression_string,expression);

    double delta = (to-from)/resolution;
    double out = 0;

    for (int i = 0; i < resolution; ++i) {
        x = from + (delta * i);
        out += expression.value() * delta;
    }

    cout << "Risultato metodo dei rettangoli:\t" << out << endl;

    out = 0;

    for (int i = 0; i < resolution; ++i) {
        x = from + (delta * i);
        double temp = expression.value();
        x = from + (delta * (i + 1));
        out += (temp+expression.value())*delta/2;
    }

    cout << "Risultato metodo dei trapezioidi:\t" << out << endl;

}

int main() {
    compute();
    return 0;
}

