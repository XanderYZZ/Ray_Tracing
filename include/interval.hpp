#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include "MathConstants.hpp"

class Interval {
public:
    static const Interval empty, universe;

    Interval() : min_value(+infinity), max_value(-infinity) {} 

    Interval(double min_value, double max_value) : min_value(min_value), max_value(max_value) {}

    double size() const {
        return max_value - min_value;
    }

    bool contains(double x) const {
        return min_value <= x && x <= max_value;
    }

    bool surrounds(double x) const {
        return min_value < x && x < max_value;
    }

    double GetMax() const { return max_value; }
    double GetMin() const { return min_value; }

private:
    double min_value, max_value;
};

const Interval Interval::empty    = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);

#endif 