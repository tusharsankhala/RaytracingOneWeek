#pragma once

#include "hitable.h"

class hitable_list : public hitable
{
public:
	hitable_list() {}
	hitable_list(hitable **l, int n) : list(l), hitList_size(n) {}

	bool hit(const Ray & ray, float t_min, float t_max, hit_record & rec) const;

public:
	hitable **list;
	int hitList_size;
};
