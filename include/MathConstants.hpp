#ifndef MATH_CONSTANTS_HPP
#define MATH_CONSTANTS_HPP

#include <limits>
#include <random>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double DegreesToRadians(const double &degrees) {
    return degrees * pi / 180.0;
}

inline double RandomDouble() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    
    return distribution(generator);
}

inline double RandomDouble(double min, double max) {
    return min + (max - min) * RandomDouble();
}

#endif 