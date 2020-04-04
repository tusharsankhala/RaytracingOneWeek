#ifndef HITABLELIST_H
#define HITABLELIST_H

#include "hitable.h"
#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hitable_list : public hitable
{
public:
	hitable_list() {}
	hitable_list(shared_ptr<hitable> object);
	
	void Clear();
	void AddObject(std::shared_ptr<hitable> object);

	virtual bool hit(const Ray& r, double tmin, double tmax, hit_record& rec) const;

public:
	std::vector<shared_ptr<hitable>> objects;
};

#endif