#pragma once

#include <math.h>

template <typename T>
class vec3
{
public:
	vec3() {}
	vec3(T e0, T e1, T e2)
	{
		e[0] = e0;
		e[1] = e1;
		e[2] = e2;
	}

	inline T x() const { return e[0]; }
	inline T y() const { return e[1]; }
	inline T z() const { return e[2]; }
	inline T r() const { return e[0]; }
	inline T g() const { return e[1]; }
	inline T b() const { return e[2]; }

	inline T operator[](int index) { return e[index]; }

private:
	T e[3];
};

using vec3f = vec3<float>;
