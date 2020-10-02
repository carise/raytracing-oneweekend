#include "ray.h"
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
vec3 color(const ray &r)
{
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main()
{
    int nx = 200;
    int ny = 100;
    const float magic = 255.99;
    const float b = 0.2;

    std::cout << "P3\n"
              << nx << " " << ny << "\n255\n";

    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            vec3 col = color(r);
            int ir = int(magic * col[0]);
            int ig = int(magic * col[1]);
            int ib = int(magic * col[2]);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    return 0;
}