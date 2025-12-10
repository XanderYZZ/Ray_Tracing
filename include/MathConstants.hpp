#ifndef MATH_CONSTANTS_HPP
#define MATH_CONSTANTS_HPP

#include <limits>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double DegreesToRadians(const double &degrees) {
    return degrees * pi / 180.0;
}

#endif 