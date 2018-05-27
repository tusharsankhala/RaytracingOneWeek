# ifndef RAYH
#define RAYH
#include "vec3.h"

class Ray
{
public:
	Ray();
	Ray(const vec3& or , const vec3& dir);
	vec3 point_at_parameter(float t) const;
	vec3 get_origin() const;
	vec3 get_direction() const;
	
	vec3 origin;
	vec3 direction;
};

#endif 