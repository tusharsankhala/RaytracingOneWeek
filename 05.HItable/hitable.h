#ifndef HITABLE_H
#define HITABLE_H

#include "ray.h"

struct hit_record
{
    vec3d p;
    vec3d normal;
    double t;
    bool front_face;

    inline void Set_Face_Normal(const Ray& r, const vec3d& outward_normal)
    {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hitable {
public:
    virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif