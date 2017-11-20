#pragma once

namespace Math {

	struct Vector3D {
		float x, y, z;

		explicit Vector3D(float a = 0.0f, float b = 0.0f,  float c = 0.0f) : x(a), y(b), z(c) {}

		inline Vector3D& operator+=(const Vector3D &right);
		inline Vector3D& operator-=(const Vector3D &right);
	};

	inline Vector3D operator+(const Vector3D &left, const Vector3D &right);
	inline Vector3D operator*(float scalar, const Vector3D &vector);
	inline Vector3D operator*(const Vector3D &vector, float scalar);

	#include "Vector3D.inl"
}