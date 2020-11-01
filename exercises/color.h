#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

void write_color(std::ostream &out, color pixel_color) {
  double magic = 255.99;

  out << static_cast<int>(magic * pixel_color.x()) << ' '
      << static_cast<int>(magic * pixel_color.y()) << ' '
      << static_cast<int>(magic * pixel_color.z()) << '\n';
}

#endif
