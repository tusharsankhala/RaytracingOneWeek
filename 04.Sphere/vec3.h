#pragma once
#pragma once

template <typename T>
class Vec3
{
public:

	// Ctors.
	Vec3() : x(T(0)), y(T(0)), z(T(0)) {}
	Vec3(T xx) : x(xx), y(xx), z(xx) {}
	Vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}

	// Vector To Scalar Arithematic Operations.
	Vec3<T> operator*(const T &f) const { return Vec3<T>(x * f, y * f, z * f); }

	// Vector To Vector Arithematic Operations.
	Vec3<T> operator+(const Vec3<T> &v) const { return Vec3<T>(x + v.x, y + v.y, z + v.z); }
	Vec3<T> operator-(const Vec3<T> &v) const { return Vec3<T>(x - v.x, y - v.y, z - v.z); }

	Vec3<T> operator*(const Vec3<T> &v) const { return Vec3<T>(x * v.x, y * v.y, z * v.z); }

	// Dot Product.
	T dot(const Vec3<T> &v) const { return (x * v.x	+ y * v.y + z * v.z); }

	// Length of the vector.
	T length2() const { return (x*x + y* y + z*z); }

	T length() const { return sqrt(length2()); }

	// Vector Normalization.
	Vec3& normalize()
	{
		// Getting the length of the vector.
		T vlen = length();

		if (vlen > 0)
		{
			T invLen = 1 / vlen;
			x *= invLen;
			y *= invLen;
			z *= invLen;
		}

		return *this;
	}

	// Vector Components. 
	T x, y, z;
};

template <typename T>
inline Vec3<T> operator*(T &f, const Vec3<T> &v)
{
	return Vec3<T>(f * v.x, f * v.y, f * v.z);
}

typedef Vec3<float> Vec3f;