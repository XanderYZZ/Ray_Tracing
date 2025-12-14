#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include <iostream> 
#include <array>
#include "MathConstants.hpp"

class vec3 {
public:
    vec3() : xyz{0, 0, 0} {};
    vec3(double x, double y, double z) : xyz{x, y, z} {};
    
    std::array<double, 3> GetXYZ() const { 
        return xyz; 
    }

    double x() const { return xyz[0]; }
    double y() const { return xyz[1]; }
    double z() const { return xyz[2]; }

    vec3 operator-() const { return vec3(-xyz[0], -xyz[1], -xyz[2]); }
    double operator[](int i) const { return xyz[i]; }
    double &operator[](int i) { return xyz[i]; } // To allow write operations by reference. 

    vec3 &operator+=(const vec3 &v) {
        xyz[0] += v.x();
        xyz[1] += v.y();
        xyz[2] += v.z();

        return *this;
    }
    
    vec3 &operator*=(double t) {
        xyz[0] *= t;
        xyz[1] *= t;
        xyz[2] *= t;

        return *this;
    }

    vec3 &operator/=(double t) {
        return *this *= 1/t;
    }

    double Length() const {
        return std::sqrt(LengthSquared());
    }

    double LengthSquared() const {
        return std::pow(xyz[0], 2) + std::pow(xyz[1], 2) + std::pow(xyz[2], 2);
    }

    bool NearZero() const {
        auto s = 1e-8;

        return (std::fabs(xyz[0]) < s) && (std::fabs(xyz[1]) < s) && (std::fabs(xyz[2]) < s);
    }

    static vec3 random() {
        return vec3(RandomDouble(), RandomDouble(), RandomDouble());
    }

    static vec3 random(double min, double max) {
        return vec3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max));
    }

private:
    std::array<double, 3> xyz;
};

// Operator declarations outside of the class definition are below.
std::ostream& operator<<(std::ostream&, const vec3&);
vec3 operator+(const vec3&, const vec3&);
vec3 operator-(const vec3&, const vec3&);
vec3 operator*(const vec3&, const vec3&);
vec3 operator*(double, const vec3&);
vec3 operator*(const vec3&, double);
vec3 operator/(const vec3&, double);

double dot(const vec3&, const vec3&);
vec3 cross(const vec3&, const vec3&);
vec3 unit_vector(const vec3&);
vec3 RandomUnitVector();
vec3 RandomOnHemisphere(const vec3& normal);
double LinearToGamma(double linear_component);
vec3 Reflect(const vec3& v, const vec3& n);

#endif 