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

    double Clamp(double x) const {
        if (x < min_value) { return min_value; }
        if (x > max_value) { return max_value; }

        return x;
    }

    double GetMax() const { return max_value; }
    double GetMin() const { return min_value; }

private:
    double min_value, max_value;
};

const inline Interval Interval::empty    = Interval(+infinity, -infinity);
const inline Interval Interval::universe = Interval(-infinity, +infinity);

#endif 