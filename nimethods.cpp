#include "nimethods.h"

NIResult NIMethods::rectangle(Expression *expression, double from, double to, unsigned int resolution) {
    double out = 0;
    double delta = (to-from)/resolution;
    vector<Point> line;
    line.reserve(2*resolution);

    expression->setX(from);
    for (unsigned int i = 0; i < resolution; ++i) {
        double y = expression->getY();
        out += expression->getY() * delta;
        line.push_back(make_pair(expression->getX(), y));
        line.push_back(make_pair(expression->getX()+delta, y));
        expression->addX(delta);
    }

    return make_pair(out, line);
}

NIResult NIMethods::trapezoidal(Expression *expression, double from, double to, unsigned int resolution) {
    double out = 0;
    double delta = (to-from)/resolution;
    vector<Point> line;
    line.reserve(2*resolution);

    expression->setX(from);
    for (unsigned int i = 0; i < resolution; ++i) {
        double y1 = expression->getY();
        expression->addX(delta);
        double y2 = expression->getY();
        out += (y1+y2)*delta/2;
        line.push_back(make_pair(expression->getX()-delta, y1));
        line.push_back(make_pair(expression->getX(), y2));
    }

    return make_pair(out, line);
}

NIResult NIMethods::simpson(Expression *expression, double from, double to, unsigned int resolution) {
    double out = 0;
    double delta = (to-from)/resolution;
    vector<Point> line;
    line.reserve(2*resolution);

    for (unsigned int i = 1; i <= resolution/2; ++i) {
        expression->setX(from + (2 * i - 2) * delta);
        out += expression->getY();
        expression->setX(from + (2 * i - 1) * delta);
        out += 4*expression->getY();
        expression->setX(from + 2 * i * delta);
        out += expression->getY();
    }

    out *= delta/3;

    return make_pair(out, line);
}
