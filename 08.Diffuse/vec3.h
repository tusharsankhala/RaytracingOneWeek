#pragma once

#include <math.h>
#include <stdlib.h>
#include <iostream>

template <typename T>

class vec3
{
public:
	vec3() {}
	vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) { }

	const vec3<T>& operator+() const { return *this; }
	vec3<T> operator-() const { return vec3(-x, -y, -z); }

	vec3<T> operator+(const vec3<T> &v2) const { return vec3<T>(x + v2.x, y + v2.y, z + v2.z); }
	vec3<T> operator-(const vec3<T> &v2) const { return vec3<T>(x - v2.x, y - v2.y, z - v2.z); }
	vec3<T> operator*(const vec3<T> &v2) const { return vec3<T>(x * v2.x, y * v2.y, z * v2.z); }
	vec3<T> operator/(const vec3<T> &v2) const { return vec3<T>(x / v2.x, y / v2.y, z / v2.z); }
	vec3<T> operator*(const T f) const { return vec3<T>(x * f, y * f, z * f); }
	vec3<T> operator/(const T f) const { return vec3<T>(x / f, y / f, z / f); }

	vec3<T>& operator+=(const vec3<T> &v) { x += v.x; y += v.y; z += v.z; return *this; }
	vec3<T>& operator*=(const vec3<T> &v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
	vec3<T>& operator/=(const vec3<T> &v) { x /= v.x; y /= v.y;	z /= v.z; return *this; }
	vec3<T>& operator-=(const vec3<T> &v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
	vec3<T>& operator*=(const T t) { x *= t;	y *= t;	z *= t;	return *this; }
	vec3<T>& operator/=(const T t) { T k = 1.0f / t; x *= k; y *= k; z *= k; return *this; }

	T length() const { return sqrt(x * x + y * y + z * z); }
	T squared_length() const { return x * x + y * y + z * z; }
	void make_unit_vector()
	{
		float k = 1.0f / sqrt(x * x + y * y + z * z);
		x *= k; y *= k; z *= k;
	}

	T dot(const vec3<T> &v2)
	{
		return x * v2.x + y * v2.y + z * v2.z;
	}

	float x, y, z;
};

typedef vec3<float> vec3f;

// A scalar multiplies a vector
template <typename T>
inline vec3<T> operator*(T t, const vec3<T> &v)
{
	return vec3<T>(t * v.x, t * v.y, t * v.z);
}

// A vector multiplies a vector
template <typename T>
inline vec3<T> operator*(const vec3<T> &v, T t)
{
	return vec3<T>(t * v.x, t * v.y, t * v.z);
}

template <typename T>
inline vec3<T> unit_vector(vec3<T> v)
{
	return v / v.length();
}