#pragma once

#include <math.h>
#include <ostream>
#include "constants.h"

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

	inline vec3<T>& operator+=(const vec3<T> vec2)
	{
		e[0] += vec2.e[0];
		e[1] += vec2.e[1];
		e[2] += vec2.e[2];

		return *this;
	}

	inline vec3<T> operator-() const { return vec3<T>(-e[0], -e[1], -e[2]); }
	inline vec3<T> operator*(const T p) { return vec3<T>(p * e[0], p * e[1], p * e[2]); }
	inline T operator[](int index) { return e[index]; }

	inline vec3<T> operator/(T val) { return vec3<T>(e[0] / val, e[1] / val, e[2] / val); }
	inline vec3<T>& operator/=(T val)
	{
		e[0] /= val;
		e[1] /= val;
		e[2] /= val;

		return *this;
	}

	inline static vec3<T> random()
	{
		return vec3<T>(random_double(), random_double(), random_double());
	}

	inline static vec3<T> random(double min, double max)
	{
		return vec3<T>(random_double(min, max), random_double(min, max), random_double(min, max));
	}

	inline static vec3<T> random_in_unit_sphere()
	{
		while (true)
		{
			auto p = vec3<T>::random(-1, 1);
			if (p.magnitude_squared() >= 1)
				continue;

			return p;
		}
	}

	inline static vec3<T> random_in_hemisphere(const vec3<T> normal)
	{
		vec3<T> in_unit_sphere = random_in_unit_sphere();

		// In the same hemisphere as the normal.
		if (in_unit_sphere.dot(normal) > 0.0)
		{
			return in_unit_sphere;
		}
		else
		{
			return -in_unit_sphere;
		}
	}

	inline double magnitude() const { return sqrt(magnitude_squared()); }
	inline double magnitude_squared() const { return (e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }

	inline vec3<T>& normalize()
	{
		// Getting lenght of the vector.
		T mag = magnitude();

		if (mag > 0)
		{
			T invLen = 1 / mag;

			e[0] *= invLen;
			e[1] *= invLen;
			e[2] *= invLen;
		}

		return *this;
	}

	inline T dot(const vec3<T>& vec) { return (e[0] * vec.r() + e[1] * vec.g() + e[2] * vec.b()); }

	friend std::ostream& operator<<(std::ostream& os, const vec3<T>& vec)
	{
		os << "[" << vec.x() << " " << vec.y() << " " << vec.z() << "]";
		return os;
	}

private:
	T e[3];
};

template <typename T>
inline vec3<T> operator+(const vec3<T>& vec1, const vec3<T>& vec2)
{
	return vec3<T>(vec1.x() + vec2.x(), vec1.y() + vec2.y(), vec1.z() + vec2.z());
}

template <typename T>
inline vec3<T> operator-(const vec3<T>& vec1, const vec3<T>& vec2)
{
	return vec3<T>(vec1.x() - vec2.x(), vec1.y() - vec2.y(), vec1.z() - vec2.z());
}

template <typename T>
inline vec3<T> operator*(const T p, const vec3<T>& vec)
{
	return vec3<T>(p * vec.x(), p * vec.y(), p * vec.z());
}

template <typename T>
inline vec3<T> operator/(const vec3<T>& vec, const T p)
{
	return vec3<T>(vec.x() / p, vec.y() / p, vec.z() / p);
}

template <typename T>
inline T dot(const vec3<T>& vec1, const vec3<T>& vec2)
{
	return (vec1.r() * vec2.r() + vec1.g() * vec2.g() + vec1.b() * vec2.b());
}

template <typename T>
inline vec3<T> normalize(const vec3<T>& vec)
{
	auto mag = vec.magnitude();
	return (vec) / mag;
}

using vec3f = vec3<float>;
using vec3d = vec3<double>;