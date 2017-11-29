using Math::Matrix3D;
using Math::Vector3D;

Matrix3D::Matrix3D(
	float pr0c0, float pr0c1, float pr0c2, 
	float pr1c0, float pr1c1, float pr1c2,
	float pr2c0, float pr2c1, float pr2c2)
{
	r0c0 = pr0c0; r0c1 = pr0c1; r0c2 = pr0c2;
	r1c0 = pr1c0; r1c1 = pr1c1; r1c2 = pr1c2;
	r2c0 = pr2c0; r2c1 = pr2c1; r2c2 = pr2c2;
}

Matrix3D Matrix3D::rotate(float angleInRadiants) {
	float sinResult = sin(angleInRadiants);
	float cosResult = cos(angleInRadiants);
	return Matrix3D(cosResult, -sinResult, 0, sinResult, cosResult, 0, 0, 0, 1);
}

Matrix3D Matrix3D::translate(const Vector3D& source) {
	return Matrix3D(1, 0, source.x, 0, 1, source.y, 0, 0, 1);
}


Matrix3D Matrix3D::scale(float x, float y) {
	return Matrix3D(x, 0, 0, 0, y, 0, 0, 0, 1);
}

Matrix3D operator+(const Matrix3D& l, const Matrix3D& r) {
	return Matrix3D(l.r0c0 + r.r0c0, l.r0c1 + r.r0c1, l.r0c2 + r.r0c2, 
		l.r1c0 + r.r1c0, l.r1c1 + r.r1c1, l.r1c2 + r.r1c2, 
		l.r2c0 + r.r2c0, l.r2c1 + r.r2c1, l.r2c2 + r.r2c2);
}

Matrix3D operator-(const Matrix3D& l, const Matrix3D& r) {
	return Matrix3D(l.r0c0 - r.r0c0, l.r0c1 - r.r0c1, l.r0c2 - r.r0c2,
		l.r1c0 - r.r1c0, l.r1c1 - r.r1c1, l.r1c2 - r.r1c2,
		l.r2c0 - r.r2c0, l.r2c1 - r.r2c1, l.r2c2 - r.r2c2);
}

Matrix3D operator*(float scalar, const Matrix3D& r) {
	return Matrix3D(scalar*r.r0c0, scalar*r.r0c1, scalar*r.r0c2, 
		scalar*r.r1c0, scalar*r.r1c1, scalar*r.r1c2, 
		scalar*r.r2c0, scalar*r.r2c1, scalar*r.r2c2);
}

Matrix3D operator*(const Matrix3D& l, float scalar) {
	return Matrix3D(scalar*l.r0c0, scalar*l.r0c1, scalar*l.r0c2,
		scalar*l.r1c0, scalar*l.r1c1, scalar*l.r1c2,
		scalar*l.r2c0, scalar*l.r2c1, scalar*l.r2c2);
}

Vector3D operator*(const Matrix3D& l, const Vector3D& r) {
	return Vector3D(l.r0c0*r.x + l.r0c1*r.y + l.r0c2*r.z,
		l.r1c0*r.x + l.r1c1*r.y + l.r1c2*r.z, 
		l.r2c0*r.x + l.r2c1*r.y + l.r2c2*r.z);
}

Matrix3D operator*(const Matrix3D& l, const Matrix3D& r) {
	return Matrix3D(
		l.r0c0*r.r0c0 + l.r0c1*r.r1c0 + l.r0c2*r.r2c0,
		l.r0c0*r.r0c1 + l.r0c1*r.r1c1 + l.r0c2*r.r2c1,
		l.r0c0*r.r0c2 + l.r0c1*r.r1c2 + l.r0c2*r.r2c2,
		l.r1c0*r.r0c0 + l.r1c1*r.r1c0 + l.r1c2*r.r2c0,
		l.r1c0*r.r0c1 + l.r1c1*r.r1c1 + l.r1c2*r.r2c1,
		l.r1c0*r.r0c2 + l.r1c1*r.r1c2 + l.r1c2*r.r2c2,
		l.r2c0*r.r0c0 + l.r2c1*r.r1c0 + l.r2c2*r.r2c0,
		l.r2c0*r.r0c1 + l.r2c1*r.r1c1 + l.r2c2*r.r2c1,
		l.r2c0*r.r0c2 + l.r2c1*r.r1c2 + l.r2c2*r.r2c2
	);
}

