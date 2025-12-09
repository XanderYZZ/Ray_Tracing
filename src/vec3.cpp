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
    return v / v.length();
}