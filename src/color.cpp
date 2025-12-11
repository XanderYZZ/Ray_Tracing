#include "color.hpp"
#include "interval.hpp"

void WriteColor(std::ostream &out, const vec3 &pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    static const Interval intensity(0.000, 0.999);
    int r_byte = int(256 * intensity.Clamp(r));
    int g_byte = int(256 * intensity.Clamp(g));
    int b_byte = int(256 * intensity.Clamp(b));

    out << r_byte << " " << g_byte << " " << b_byte << "\n";
}