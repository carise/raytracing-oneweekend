#include "color.h"
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
