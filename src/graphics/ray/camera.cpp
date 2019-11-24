#include "camera.hpp"

using namespace mpl::graphics;
using namespace mpl::math;

Camera::Camera() :
	m_origin(0.0, 0.0, 0.0),
	m_lower_left_corner(-2.0, -1.0, -1.0),
	m_horizontal(4.0, 0.0, 0.0),
	m_vertical(0.0, 2.0, 0.0)
{
}

Camera::~Camera()
{
}

Ray mpl::graphics::Camera::CreateRay(double screen_u, double screen_v) const
{
	return { m_origin, m_lower_left_corner + (screen_u * m_horizontal) + (screen_v * m_vertical) };
}
