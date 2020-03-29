#pragma once

#include "vec3.h"

class Ray
{
public:
    Ray() : A(vec3f(0.0f, 0.0f, 0.0f)), B(vec3f(1.0f, 0.0f, 0.0f)) {}
    Ray(vec3f _A, vec3f _B) : A(_A), B(_B) {}

    vec3f origin() const { return A; }
    vec3f direction() const { return B; }
    vec3f point_at_parameter(const float t) const { return A + (t * B); }

private:
    vec3f A;        // Starting Postion.
    vec3f B;        // Ray Direction.
};