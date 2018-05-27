# ifndef RAYH
#define RAYH
#include "vec3.h"

class Ray
{
public:
	Ray();
	Ray(const vec3f& or , const vec3f& dir);
	vec3f point_at_parameter(float t) const;
	vec3f get_origin() const;
	vec3f get_direction() const;

	vec3f origin;
	vec3f direction;
};

#endif 