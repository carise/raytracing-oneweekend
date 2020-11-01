#include "color.h"
#include "vec3.h"
#include <iostream>

/* Output a PPM file.
 *
 * Pixels are written in rows, left to right.
 * Rows are written out, top to bottom.
 */
int main() {
  const int image_width = 256;
  const int image_height = 256;

  const float b = 0.2;

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; j--) {
    std::cerr << "\nScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; i++) {
      color pixel_color(double(i) / (image_width - 1),
                        double(j) / (image_height - 1), 0.25);
      write_color(std::cout, pixel_color);
    }
  }

  std::cerr << "\nDone.\n";
  return 0;
}