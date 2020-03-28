#pragma once

#include "vec3.h"

class Ray
{
public:
    Ray() {}
    Ray(vec3f _A, vec3f _B) : A(_A), B(_B) {}

    vec3f origin() const { return A; }
    vec3f direction() const { return B; }
    vec3f parameter_at_point(const float t) const { return A + (t * B); }

private:
    vec3f A;        // Starting Postion.
    vec3f B;        // Ray Direction.
};