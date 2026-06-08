#include <iostream>

/* Output a PPM file.
 *
 * Pixels are written in rows, left to right.
 * Rows are written out, top to bottom.
 */
int main() {
  const int image_width = 256;
  const int image_height = 256;
  const double magic = 255.999;

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; j--) {
    std::clog << "\nScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; i++) {
      auto r = double(i) / (image_width-1);
      auto g = double(j) / (image_height-1);
      auto b = 0.0;

      int ir = int(magic * r);
      int ig = int(magic * g);
      int ib = int(magic * b);

      std::cout << ir << ' ' << ig << ' ' << ib << '\n';
    }
  }

  std::clog << "\nDone.\n";
  return 0;
}
