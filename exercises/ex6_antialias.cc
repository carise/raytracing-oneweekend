#include "camera.h"
#include "hitable_list.h"
#include "sphere.h"
#include <cstdlib>
#include <iostream>

/* Anti-aliasing.
 */

/* Computes the color for the ray.
 *
 * Builds off exercise 4, where the ray tracer created sphere if the point
 * satisfied the equation of a sphere.
 *
 * In this exercise, we shade the sphere by mapping the vector to x/y/z and
 * then to r/g/b.
 */
vec3 color(const ray &r, hitable *world) {
  hit_record rec;
  if (world->hit(r, 0.0, MAXFLOAT, rec)) {
    return 0.5 *
           vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
  }

  // color the background
  vec3 unit_direction = unit_vector(r.direction());
  float t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

double clamp(double x, double min, double max) {
  if (x < min)
    return min;
  if (x > max)
    return max;
  return x;
}

int main() {
  int nx = 200;
  int ny = 100;
  int ns = 100;

  const float magic = 255.99;

  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  hitable *list[2];
  list[0] = new sphere(vec3(0, 0, -1), 0.5);
  list[1] = new sphere(vec3(0, -100.5, -1), 100);
  hitable *world = new hitable_list(list, 2);
  camera cam;

  for (int j = ny - 1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      vec3 col(0, 0, 0);
      for (int s = 0; s < ns; s++) {
        float u = (float(i) + drand48()) / float(nx);
        float v = (float(j) + drand48()) / float(ny);
        ray r = cam.get_ray(u, v);
        col += color(r, world);
      }

      col /= float(ns);
      int ir = int(magic * col[0]);
      int ig = int(magic * col[1]);
      int ib = int(magic * col[2]);
      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }

  return 0;
}