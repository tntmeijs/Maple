#include "ray.hpp"

using namespace mpl::graphics;
using namespace mpl::math;

Ray::Ray() :
	m_origin(0.0, 0.0, 0.0),
	m_direction(0.0, 0.0, -1.0)
{
}

Ray::Ray(const Vector3& start, const Vector3& end) :
	m_origin(start),
	m_direction(end)
{
}

Ray::~Ray()
{
}

const Vector3& Ray::Origin() const
{
	return m_origin;
}

const Vector3& Ray::Direction() const
{
	return m_direction;
}

const Vector3 Ray::PointAt(double distance) const
{
	return m_origin + (m_direction * distance);
}

Vector3 Ray::Reflect(const Ray& ray, const Vector3& normal) const
{
	// The normal is assumed to be normalized already, as the name would imply
	Vector3 normalized_direction = ray.Direction().Normalized();
	return normalized_direction - (2.0 * normalized_direction.Dot(normal) * normal);
}
