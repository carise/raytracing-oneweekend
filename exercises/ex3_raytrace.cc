#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

/* A simple ray tracer.
 *
 * (From the book) The ray tracer sends rays through pixels
 * and computes the color seen in the direction of the rays.
 * i.e. Calculate which ray goes from eye to pixel, compute
 * what that ray intersects, and compute a color for that
 * intersection point.
 *
 * (From the book) The eye of the camera is at (0, 0, 0).
 * The y-axis goes up, and the x-axis goes right. The screen
 * is the negative z-axis.
 */

/* Computes the color for the ray.
 *
 * Blends white and blue depending on the y-coordinate. Blue
 * is at 1.0 ("top"), and white is at 0.0 ("bottom").
 *
 * This forms a linear interpolation, in the form of:
 *
 * blended_value = (1-t)*start_value + t*end_value, where
 * t = [0,1]
 */

color ray_color(const ray& r) {
  vec3 unit_direction = unit_vector(r.direction());
  auto a = 0.5*(unit_direction.y() + 1.0);
  return (1.0-a) * color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main()
{
  auto aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;

  int image_height = int(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  // Camera
  auto focal_length = 1.0;
  auto viewport_height = 2.0;
  auto viewport_width = viewport_height * (double(image_width) / image_height);
  auto camera_center = point3(0, 0, 0);

  // Vectors across horizontal and down the viewport edges
  auto viewport_u = vec3(viewport_width, 0, 0);
  auto viewport_v = vec3(0, -viewport_height, 0);

  // Horizontal/vertical delta vectors from pixel to pixel
  auto pixel_delta_u = viewport_u / image_width;
  auto pixel_delta_v = viewport_v / image_height;

  // Location of upper-left pixel
  auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
  auto pixel00_loc = viewport_upper_left + 0.5*(pixel_delta_u + pixel_delta_v);

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (int j = 0; j < image_height; j++) {
    std::clog << "\nScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; i++) {
      auto pixel_center = pixel00_loc + (i*pixel_delta_u) + (j*pixel_delta_v);
      auto ray_direction = pixel_center - camera_center;
      ray r(camera_center, ray_direction);

      color pixel_color = ray_color(r);
      write_color(std::cout, pixel_color);
    }
  }

  std::clog << "\nDone.\n";
  return 0;
}
