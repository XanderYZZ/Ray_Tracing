#ifndef MATERIAL_HPP
#define MATERIAL_HPP 

#include "hittable.hpp"
#include "vec3.hpp"

class Material {
public:
    virtual ~Material() = default;

    virtual bool Scatter(const ray &r_in, const HitRecord &rec, vec3 &attenuation, ray &scattered) const {
        return false;
    }
};

class Lambertian : public Material {
public:
    Lambertian(const vec3 &albedo) : albedo(albedo) {};
    bool Scatter(const ray &r_in, const HitRecord &rec, vec3 &attenuation, ray &scattered) const override {
        auto scatter_direction = rec.normal + RandomUnitVector();

        if (scatter_direction.NearZero()) {
            scatter_direction = rec.normal;
        }

        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;

        return true;
    }

private:
    vec3 albedo;
};

class Metal : public Material {
public:
    Metal(const vec3& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

    bool Scatter(const ray& r_in, const HitRecord& rec, vec3& attenuation, ray& scattered) const override {
        vec3 reflected = Reflect(r_in.GetDirection(), rec.normal);
        reflected = unit_vector(reflected) + (fuzz * RandomUnitVector());
        scattered = ray(rec.p, reflected);
        attenuation = albedo;

        return (dot(scattered.GetDirection(), rec.normal) > 0);
    }

private:
    vec3 albedo;
    double fuzz;
};

#endif