#include "camera.hpp"
#include "HittableList.hpp"
#include "sphere.hpp"

int main() {
    HittableList world;

    world.add(std::make_shared<Sphere>(vec3(0,0,-1), 0.5));
    world.add(std::make_shared<Sphere>(vec3(0,-100.5,-1), 100));

    Camera camera(16.0 / 9.0, 400, 100);
    camera.Render(world);
}