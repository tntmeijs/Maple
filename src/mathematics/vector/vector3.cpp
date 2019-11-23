#include "vector3.hpp"

mpl::math::Vector3::Vector3()
{
	x(0.0);
	y(0.0);
	z(0.0);
}

mpl::math::Vector3::Vector3(double initial_xyz)
{
	x(initial_xyz);
	y(initial_xyz);
	z(initial_xyz);
}

mpl::math::Vector3::Vector3(double initial_x, double initial_y, double initial_z)
{
	x(initial_x);
	y(initial_y);
	z(initial_z);
}

mpl::math::Vector3::~Vector3()
{
}

double mpl::math::Vector3::x() const
{
	return m_memory[0];
}

double mpl::math::Vector3::y() const
{
	return m_memory[1];
}

double mpl::math::Vector3::z() const
{
	return m_memory[2];
}

void mpl::math::Vector3::x(double x)
{
	m_memory[0] = x;
}

void mpl::math::Vector3::y(double y)
{
	m_memory[1] = y;
}

void mpl::math::Vector3::z(double z)
{
	m_memory[2] = z;
}

double mpl::math::Vector3::r() const
{
	return x();
}

double mpl::math::Vector3::g() const
{
	return y();
}

double mpl::math::Vector3::b() const
{
	return z();
}

void mpl::math::Vector3::r(double r)
{
	x(r);
}

void mpl::math::Vector3::g(double g)
{
	y(g);
}

void mpl::math::Vector3::b(double b)
{
	z(b);
}
