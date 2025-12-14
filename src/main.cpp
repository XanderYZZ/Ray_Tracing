#include "camera.hpp"
#include "HittableList.hpp"
#include "sphere.hpp"
#include "Material.hpp"

int main() {
    HittableList world;

    auto material_ground = std::make_shared<Lambertian>(vec3(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Lambertian>(vec3(0.1, 0.2, 0.5));
    auto material_left   = std::make_shared<Metal>(vec3(0.8, 0.8, 0.8), 0.3);
    auto material_right  = std::make_shared<Metal>(vec3(0.8, 0.6, 0.2), 1.0);

    world.add(std::make_shared<Sphere>(vec3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<Sphere>(vec3( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(std::make_shared<Sphere>(vec3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(std::make_shared<Sphere>(vec3( 1.0,    0.0, -1.0),   0.5, material_right));

    Camera camera(16.0 / 9.0, 400, 100, 50);
    camera.Render(world);
}