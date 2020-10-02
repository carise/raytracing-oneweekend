#include <iostream>

/* Output a PPM file.
 *
 * Pixels are written in rows, left to right.
 * Rows are written out, top to bottom.
 */
int main() {
  int nx = 200;
  int ny = 100;
  const float magic = 255.99;
  const float b = 0.2;

  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  for (int j = ny - 1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      float r = float(i) / float(nx);
      float g = float(j) / float(ny);
      int ir = int(magic * r);
      int ig = int(magic * g);
      int ib = int(magic * b);
      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }

  return 0;
}