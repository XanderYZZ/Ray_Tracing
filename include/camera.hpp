#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "hittable.hpp"
#include "color.hpp"

class Camera {
public:
    Camera(const double &aspect_ratio, const double &image_width, const double &samples_per_pixel) 
    : aspect_ratio(aspect_ratio), image_width(image_width), samples_per_pixel(samples_per_pixel) {};

    void Render(const Hittable &world) {
        Initialize();

        std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                vec3 pixel_color(0,0,0);

                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    ray r = GetRay(i, j);
                    pixel_color += RayColor(r, world);
                }

                WriteColor(std::cout, pixel_samples_scale * pixel_color);
            }
        }
    }

private:
    void Initialize() {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        center = vec3(0, 0, 0);

        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (double(image_width)/image_height);

        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        auto viewport_upper_left =
            center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
        pixel_samples_scale = 1.0 / samples_per_pixel;
    }

    vec3 RayColor(const ray &r, const Hittable &world) const {
        HitRecord rec;

        if (world.Hit(r, rec, Interval(0, infinity))) {
            return 0.5 * (rec.normal + vec3(1,1,1));
        }

        vec3 unit_direction = unit_vector(r.GetDirection());
        auto a = 0.5 * (unit_direction.y() + 1.0);

        return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0);
    }

    ray GetRay(int i, int j) const {
        auto offset = SampleSquare();
        auto pixel_sample = pixel00_loc
                          + ((i + offset.x()) * pixel_delta_u)
                          + ((j + offset.y()) * pixel_delta_v);
        auto ray_origin = center;
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    vec3 SampleSquare() const {
        return vec3(RandomDouble() - 0.5, RandomDouble() - 0.5, 0);
    }

    int          image_height;   
    vec3         center;       
    vec3         pixel00_loc;    
    vec3         pixel_delta_u;  
    vec3         pixel_delta_v;  
    double       aspect_ratio = 16.0 / 9.0;
    int          image_width = 400;
    int          samples_per_pixel = 10;
    double       pixel_samples_scale;
};

#endif 