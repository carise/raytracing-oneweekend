#include <iostream>
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"

/* Sphere and surface normals.
 *
 * Builds off exercise 3, the simple ray tracer.
 * 
 * A sphere centered at the origin of radius R is:
 * 
 * x*x + y*y + z*z = R*R
 * 
 * A surface normal is a vector that is perpendiculr
 * to the surface and points out. The normal for a
 * sphere is in the direction of the hit point minus
 * the center. The normal is assumed to be a unit vector.
 */

/* Computes the color for the ray.
 *
 * Builds off exercise 4, where the ray tracer created sphere if the point
 * satisfied the equation of a sphere.
 * 
 * In this exercise, we shade the sphere by mapping the vector to x/y/z and
 * then to r/g/b.
 */
vec3 color(const ray &r, hitable *world)
{
    hit_record rec;
    if (world->hit(r, 0.0, MAXFLOAT, rec))
    {
        return 0.5 * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
    }

    // color the background
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

    hitable *list[2];
    list[0] = new sphere(vec3(0, 0, -1), 0.5);
    list[1] = new sphere(vec3(0, -100.5, -1), 100);
    hitable *world = new hitable_list(list, 2);

    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);

            vec3 p = r.point_at_parameter(2.0);
            vec3 col = color(r, world);
            int ir = int(magic * col[0]);
            int ig = int(magic * col[1]);
            int ib = int(magic * col[2]);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    return 0;
}