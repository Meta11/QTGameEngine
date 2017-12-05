using Math::Vector3D;

Vector3D operator+(const Vector3D &left, const Vector3D &right) {
	return Vector3D(left.x + right.x, left.y + right.y, left.z + right.z);
}

Vector3D operator-(const Vector3D &left, const Vector3D &right) {
	return Vector3D(left.x - right.x, left.y - right.y, left.z - right.z);
}

Vector3D operator*(float scalar, const Vector3D &vector) {
	return Vector3D(scalar * vector.x, scalar * vector.y, scalar * vector.z);
}

Vector3D operator*(const Vector3D &vector, float scalar) {
	return Vector3D(scalar * vector.x, scalar * vector.y, scalar * vector.z);
}

Vector3D& Vector3D::operator+=(const Vector3D &right) {

	x += right.x;
	y += right.y;
	z += right.z;

	return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D &right) {

	x -= right.x;
	y -= right.y;
	z -= right.z;

	return *this;
}

float Vector3D::dot(const Vector3D& other) const {
	return (x*other.x + y*other.y + z*other.z);
}

float Vector3D::magnitude() const {
	return sqrt(magnitudeSquared());
}

float Vector3D::magnitudeSquared() const {
	return (this->dot(*this));
}

Vector3D Vector3D::normalize() const{
	float normalization = this->magnitude();
	return Vector3D(x / normalization, y / normalization, z / normalization);
}

Vector3D Vector3D::perpCw() const {
	return Vector3D(y, -x);
}

Vector3D Vector3D::perpCcw() const {
	return Vector3D(-y, x);
}

Vector3D Vector3D::projectOnto(const Vector3D& target) const {
	return (this->dot(target) / target.magnitudeSquared()) * target;
}