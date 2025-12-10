#ifndef HITTABLE_LIST_HPP
#define HITTABLE_LIST_HPP

#include "hittable.hpp"

#include <memory>
#include <vector>

class HittableList : public Hittable {
public:
    HittableList() {}
    HittableList(std::shared_ptr<Hittable> object) { add(object); }

    void clear() { objects.clear(); }

    void add(std::shared_ptr<Hittable> object) {
        objects.push_back(object);
    }

    bool Hit(const ray &r, HitRecord &rec, Interval ray_t) const override {
        HitRecord temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.GetMax();

        for (const auto& object : objects) {
            if (object->Hit(r, temp_rec, Interval(ray_t.GetMin(), closest_so_far))) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }

private:
    std::vector<std::shared_ptr<Hittable>> objects;
};

#endif 