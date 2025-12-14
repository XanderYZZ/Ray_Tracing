#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "ray.hpp"
#include "interval.hpp"

class Material;

struct HitRecord {
public:
    vec3 p;
    vec3 normal;
    double t;
    bool front_face;
    std::shared_ptr<Material> mat;

    void SetFaceNormal(const ray &r, const vec3 &outward_normal) {
        front_face = dot(r.GetDirection(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

// This one is a class just to make it clearer that it is meant to be an abstract class. 
class Hittable {
public:
    virtual ~Hittable() = default;
    virtual bool Hit(const ray& r, HitRecord& rec, Interval ray_t) const = 0;
};

#endif 