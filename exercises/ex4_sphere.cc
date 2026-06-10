#include "color.h"
#include "vec3.h"

#include <iostream>

/* Create a sphere.
 *
 * Builds off exercise 3, the simple ray tracer.
 *
 * A sphere centered at the origin of radius R is:
 *
 * x*x + y*y + z*z = R*R
 */

bool hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return discriminant >= 0;
}

/* Computes the color for the ray.
 *
 * Builds off exercise 3, where the ray tracer colored the
 * pixels from white to blue (depending on y coordinate).
 *
 * If the ray hits the sphere, return a red color.
 */
color ray_color(const ray &r)
{
    if (hit_sphere(point3(0, 0, -1), 0.5, r))
    {
        return color(1, 0, 0);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main()
{
  const int image_width = 256;
  const int image_height = 256;

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; j--) {
    std::clog << "\nScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; i++) {
      auto pixel_color = color(double(i) / (image_width-1), double(j) / (image_height-1), 0);
      write_color(std::cout, pixel_color);
    }
  }

  std::clog << "\nDone.\n";
  return 0;
}
