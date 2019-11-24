#include "vector3.hpp"

#include <math.h>

using namespace mpl::math;

Vector3::Vector3()
{
	X(0.0);
	Y(0.0);
	Z(0.0);
}

Vector3::Vector3(double initial_xyz)
{
	X(initial_xyz);
	Y(initial_xyz);
	Z(initial_xyz);
}

Vector3::Vector3(double initial_x, double initial_y, double initial_z)
{
	X(initial_x);
	Y(initial_y);
	Z(initial_z);
}

Vector3::~Vector3()
{
}

const Vector3& Vector3::operator+() const
{
	return *this;
}

const Vector3 Vector3::operator-() const
{
	return { -X(), -Y(), -Z() };
}

Vector3 mpl::math::operator+(const Vector3 a, const Vector3 b)
{
	return { a.X() + b.X(), a.Y() + b.Y(), a.Z() + b.Z() };
}

Vector3 mpl::math::operator-(const Vector3 a, const Vector3 b)
{
	return { a.X() - b.X(), a.Y() - b.Y(), a.Z() - b.Z() };
}

Vector3 mpl::math::operator*(const Vector3 a, const Vector3 b)
{
	return { a.X() * b.X(), a.Y() * b.Y(), a.Z() * b.Z() };
}

Vector3 mpl::math::operator/(const Vector3 a, const Vector3 b)
{
	return { a.X() / b.X(), a.Y() / b.Y(), a.Z() / b.Z() };
}

double Vector3::operator[](std::size_t index) const
{
	return m_memory[index];
}

double& Vector3::operator[](std::size_t index)
{
	return m_memory[index];
}

Vector3& Vector3::operator+=(const Vector3& other)
{
	X(X() + other.X());
	Y(Y() + other.Y());
	Z(Z() + other.Z());
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	X(X() - other.X());
	Y(Y() - other.Y());
	Z(Z() - other.Z());
	return *this;
}

Vector3& Vector3::operator*=(const Vector3& other)
{
	X(X() * other.X());
	Y(Y() * other.Y());
	Z(Z() * other.Z());
	return *this;
}

Vector3& Vector3::operator/=(const Vector3& other)
{
	X(X() / other.X());
	Y(Y() / other.Y());
	Z(Z() / other.Z());
	return *this;
}

Vector3& Vector3::operator*=(const double scalar)
{
	X(X() * scalar);
	Y(Y() * scalar);
	Z(Z() * scalar);
	return *this;
}

Vector3& Vector3::operator/=(const double scalar)
{
	X(X() / scalar);
	Y(Y() / scalar);
	Z(Z() / scalar);
	return *this;
}

double Vector3::X() const
{
	return m_memory[0];
}

double Vector3::Y() const
{
	return m_memory[1];
}

double Vector3::Z() const
{
	return m_memory[2];
}

void Vector3::X(double x)
{
	m_memory[0] = x;
}

void Vector3::Y(double y)
{
	m_memory[1] = y;
}

void Vector3::Z(double z)
{
	m_memory[2] = z;
}

double Vector3::R() const
{
	return X();
}

double Vector3::G() const
{
	return Y();
}

double Vector3::B() const
{
	return Z();
}

void Vector3::R(double r)
{
	X(r);
}

void Vector3::G(double g)
{
	Y(g);
}

void Vector3::B(double b)
{
	Z(b);
}

double Vector3::Length() const
{
	return ((X() * X()) + (Y() * Y()) + (Z() * Z()));
}

double Vector3::LengthSquared() const
{
	return sqrt(Length());
}

void Vector3::Normalize()
{
	double magnitude = 1.0 / LengthSquared();
	X(X() * magnitude);
	Y(Y() * magnitude);
	Z(Z() * magnitude);
}

Vector3 Vector3::Normalized() const
{
	double magnitude = 1.0 / LengthSquared();
	double x = X() * magnitude;
	double y = Y() * magnitude;
	double z = Z() * magnitude;

	return { x, y, z };
}

double Vector3::Dot(const Vector3& other) const
{
	return ((X() * other.X()) + (Y() * other.Y()) + (Z() * other.Z()));
}

Vector3 Vector3::Cross(const Vector3& other) const
{
	double cross_x = (Y() * other.Z()) - (Z() * other.Y());
	double cross_y = (Z() * other.X()) - (X() * other.Z());
	double cross_z = (X() * other.Y()) - (Y() * other.X());
	return { cross_x, cross_y, cross_z };
}

Vector3 Vector3::LerpTo(const Vector3& target, double step)
{
	double lerp_x = ((1.0 - step) * X()) + (step * target.X());
	double lerp_y = ((1.0 - step) * Y()) + (step * target.Y());
	double lerp_z = ((1.0 - step) * Z()) + (step * target.Z());
	return { lerp_x, lerp_y, lerp_z };
}
