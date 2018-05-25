#pragma once

template <typename T>
class Vec3
{
public:

	// Ctors.
	Vec3() : x(T(0)), y(T(0)), z(T(0)) {}
	Vec3(T xx) : x(xx), y(xx), z(xx) {}
	Vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}

	// Vector Components. 
	T x, y, z;
};
