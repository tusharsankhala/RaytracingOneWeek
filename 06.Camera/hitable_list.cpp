#include "hitable_list.h"

//	In order to determine whether all objects in the list were hit by light, judge one at a time.
//	If it is hit, the collision point information is stored in the hit_record structure.
//	We can see that rec is probably written more than once, and the final saved value is the latter value, which is the actual value is the latter value.
//	That is, the effective collision point of the object closest to the observation point 
//	("effective collision point": for a single object, a local effective collision point will be screened;
//	For multiple objects, the final effective overall impact point is filtered from the respective local effective impact points of all individual objects).
//	Because no matter how many collision points the light hits in sequence,
//	What we can see is just the closest collision point to us.

// If the current collision point is within the range, set the distance of the current collision point to the maximum value of the range.
//	That is, only the collision point closer to the collision point is considered later.
//	The trend is: Finding the collision point is getting closer and closer, eventually finding the nearest collision point.

bool hitable_list::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const
{
	hit_record temp_rec;
	bool hit_anything = false;
	double closest_so_far = t_max;
	for (int i = 0; i < list_size; i++)
	{
		if (list[i]->hit(r, t_min, closest_so_far, temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;
}
