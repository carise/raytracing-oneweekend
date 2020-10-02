#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

class sphere: public hitable{
    public :
        sphere(){}
        sphere(vec3 sphere_center, float r): center(sphere_center), radius(r) {};
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
        vec3 center;
        float radius;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record &rec) const 
{
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b =  dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;
    if (discriminant > 0) {
        // code is a bit redundant, maybe clean it up later?
        float t_current = (-b - sqrt(discriminant))/a;
        if (t_current < t_max && t_current > t_min) {
            rec.t = t_current;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center ) / radius;
            return true;
        }
        t_current = (-b + sqrt(discriminant))/a;
        if (t_current < t_max && t_current > t_min) {
            rec.t = t_current;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center ) / radius;
            return true;
        }
    }
    return false;
}

#endif