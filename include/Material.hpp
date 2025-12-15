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

class Dielectric : public Material {
public:
    Dielectric(double refraction_index) : refraction_index(refraction_index) {}

    bool Scatter(const ray& r_in, const HitRecord& rec, vec3& attenuation, ray& scattered)
    const override {
        attenuation = vec3(1.0, 1.0, 1.0);
        double ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;
        vec3 unit_direction = unit_vector(r_in.GetDirection());
        double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

        bool cannot_refract = ri * sin_theta > 1.0;
        vec3 direction;

        if (cannot_refract || Reflectance(cos_theta, ri) > RandomDouble()) {
            direction = Reflect(unit_direction, rec.normal);
        } else {
            direction = Refract(unit_direction, rec.normal, ri);
        }

        scattered = ray(rec.p, direction);

        return true;
    }

private:
    double refraction_index;

    static double Reflectance(double cosine, double refraction_index) {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1 - refraction_index) / (1 + refraction_index);
        r0 = r0 * r0;

        return r0 + (1-r0) * std::pow((1 - cosine), 5);
    }
};

#endif