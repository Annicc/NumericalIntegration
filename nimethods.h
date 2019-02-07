#ifndef NIMETHODS_H
#define NIMETHODS_H

#include <utility>

#include "expression.h"

using namespace std;

typedef pair<double, double> Point;
typedef pair<double, vector<Point>> NIResult;

class NIMethods {
public:
    static NIResult rectangle(Expression *expression, double from, double to, unsigned int resolution);
    static NIResult trapezoidal(Expression *expression, double from, double to, unsigned int resolution);
    static NIResult simpson(Expression *expression, double from, double to, unsigned int resolution);
};

#endif // NIMETHODS_H
