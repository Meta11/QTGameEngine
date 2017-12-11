#pragma once
#include <cmath>

namespace Math {

	struct __declspec(dllexport) Vector3D {
		float x, y, z;

		explicit Vector3D(float a = 0.0f, float b = 0.0f,  float c = 0.0f) : x(a), y(b), z(c) {}

		inline Vector3D& operator+=(const Vector3D &right);
		inline Vector3D& operator-=(const Vector3D &right);
		inline float dot(const Vector3D& other) const;
		inline float magnitude() const;
		inline float magnitudeSquared() const;
		inline Vector3D Vector3D::normalize() const;
		inline Vector3D perpCw() const;
		inline Vector3D perpCcw() const;
		inline Vector3D projectOnto(const Vector3D& target) const;
	};

	inline Vector3D operator+(const Vector3D &left, const Vector3D &right);
	inline Vector3D operator-(const Vector3D &left, const Vector3D &right);
	inline Vector3D operator*(float scalar, const Vector3D &vector);
	inline Vector3D operator*(const Vector3D &vector, float scalar);
	inline Vector3D lerp(const Vector3D& source, const Vector3D& target, const float alpha);

	#include "Vector3D.inl"
}