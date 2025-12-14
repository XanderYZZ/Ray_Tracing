#include "vec3.hpp"

std::ostream &operator<<(std::ostream &out, const vec3 &v) {
    return out << "(" << v.x() << ", " << v.y() << ", " << v.z() << ")";
} 

vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

vec3 operator*(double t, const vec3 &v) {
    return vec3(t * v.x(), t * v.y(), t * v.z());
}

vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

vec3 operator/(const vec3 &v, double t) {
    return (1/t) * v;
}

double dot(const vec3 &u, const vec3 &v) {
    return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}

vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.y() * v.z() - u.z() * v.y(), 
                u.z() * v.x() - u.x() * v.z(),
                u.x() * v.y() - u.y() * v.x());
}

vec3 unit_vector(const vec3 &v) {
    return v / v.Length();
}

vec3 RandomUnitVector() {
    while (true) {
        auto p = vec3::random(-1,1);
        auto lensq = p.LengthSquared();

        if (1e-160 < lensq && lensq <= 1) {
            return p / std::sqrt(lensq);
        }
    }
}

vec3 RandomOnHemisphere(const vec3& normal) {
    vec3 on_unit_sphere = RandomUnitVector();

    if (dot(on_unit_sphere, normal) > 0.0) {
        return on_unit_sphere;
    } else {
        return -on_unit_sphere;
    }
}

double LinearToGamma(double linear_component) {
    if (linear_component > 0) { return std::sqrt(linear_component); }

    return 0;
}