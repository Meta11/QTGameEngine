#pragma once
#include "Vector3D.h"
#include <cmath>

namespace Math {

	struct Matrix3D {
		float r0c0, r0c1, r0c2;
		float r1c0, r1c1, r1c2;
		float r2c0, r2c1, r2c2;

		inline explicit Matrix3D(
			float r0c0 = 1, float r0c1 = 0, float r0c2 = 0,
			float r1c0 = 0, float r1c1 = 1, float r1c2 = 0,
			float r2c0 = 0, float r2c1 = 0, float r2c2 = 1);

		inline static Matrix3D rotate(float angleInRadiants = 0);
		inline static Matrix3D translate(const Vector3D& source = Vector3D(0.0f, 0.0f, 0.0f));
		inline static Matrix3D scale(const Vector3D& source = Vector3D(1.0f, 1.0f, 1.0f));
	};

	inline Matrix3D operator+(const Matrix3D& l, const Matrix3D& r);
	inline Matrix3D operator-(const Matrix3D& l, const Matrix3D& r);
	inline Matrix3D operator*(const Matrix3D& l, float scalar);
	inline Matrix3D operator*(float scalar, const Matrix3D& r);
	inline Vector3D operator*(const Matrix3D& l, const Vector3D& r);
	inline Matrix3D operator*(const Matrix3D& l, const Matrix3D& r);

#include "Matrix3D.inl"

}