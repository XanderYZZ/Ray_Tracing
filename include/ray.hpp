#ifndef RAY_HPP
#define RAY_HPP

#include "vec3.hpp"

class ray {
public:
    ray() {};
    ray (const vec3 &origin, const vec3 &direction) : origin(origin), direction(direction) {};
    const vec3& GetOrigin() const { return origin; }
    const vec3& GetDirection() const { return direction; }
    vec3 At(double t) const {
        return origin + (t * direction);
    }

private:
    vec3 origin;
    vec3 direction;
};

#endif 