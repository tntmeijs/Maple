#include "ray.hpp"

using namespace mpl::graphics;
using namespace mpl::math;

mpl::graphics::Ray::Ray() :
	m_origin({ 0.0, 0.0, 0.0 }),
	m_direction({ 0.0, 0.0, -1.0 })
{
}

mpl::graphics::Ray::Ray(const math::Vector3& start, const math::Vector3& end) :
	m_origin(start),
	m_direction(end)
{
}

mpl::graphics::Ray::~Ray()
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
