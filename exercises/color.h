#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

void write_color(std::ostream &out, color pixel_color) {
  double magic = 255.99;
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  int rbyte = int(magic * r);
  int gbyte = int(magic * g);
  int bbyte = int(magic * b);

  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif
