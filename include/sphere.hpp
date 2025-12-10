#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hittable.hpp"

class Sphere : public Hittable {
public:
    Sphere(const vec3 &center, double radius) : center(center), radius(std::fmax(0, radius)) {};

    bool Hit(const ray& r, HitRecord& rec, Interval ray_t) const override {
        vec3 oc = center - r.GetOrigin();
        auto a = r.GetDirection().LengthSquared();
        auto h = dot(r.GetDirection(), oc);
        auto c = oc.LengthSquared() - std::pow(radius, 2);
        auto discriminant = std::pow(h, 2) - a * c;

        if (discriminant < 0) { return false; }

        auto sqrtd = std::sqrt(discriminant);
        auto root = (h - sqrtd) / a;

        if (!ray_t.surrounds(root)) {
            root = (h + sqrtd) / a;

            if (!ray_t.surrounds(root)) {
                return false; 
            }
        }

        rec.t = root;
        rec.p = r.At(rec.t);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.SetFaceNormal(r, outward_normal);

        return true;
    }

private:
    vec3 center;
    double radius; 
};

#endif 