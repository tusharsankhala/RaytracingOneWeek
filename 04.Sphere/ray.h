#pragma once

#include "vec3.h"

class Ray
{
public:
    Ray(): orig(vec3d(0.0, 0.0, 0.0)), dir(vec3d(1.0, 0.0, 0.0)) {}
    Ray(vec3d _orig, vec3d _dir) : orig(_orig), dir(_dir) {}

    vec3d origin() const { return orig; }
    vec3d direction() const { return dir; }
    vec3d parameter_at_point(const double t) const { return orig + (t * dir); }

private:
    vec3d orig;        // Starting Postion.
    vec3d dir;         // Ray Direction.
};