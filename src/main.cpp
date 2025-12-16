#include "camera.hpp"
#include "HittableList.hpp"
#include "sphere.hpp"
#include "Material.hpp"

int main() {
    HittableList world;

    auto ground_material = std::make_shared<Lambertian>(vec3(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(vec3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = RandomDouble();
            vec3 center(a + 0.9 * RandomDouble(), 0.2, b + 0.9 * RandomDouble());

            if ((center - vec3(4, 0.2, 0)).Length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // Making diffuse here.
                    auto albedo = vec3::random() * vec3::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // Making metal here.
                    auto albedo = vec3::random(0.5, 1);
                    auto fuzz = RandomDouble(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // Making glass here.
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(vec3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(vec3(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(vec3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(vec3(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(vec3(4, 1, 0), 1.0, material3));

    Camera camera(16.0 / 9.0, 1200, 10, 50, 20, vec3(13, 2, 3), vec3(0, 0, 0), vec3(0, 1, 0), 0.6, 10.0);

    camera.Render(world);
}