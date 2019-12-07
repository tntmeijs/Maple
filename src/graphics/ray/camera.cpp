#include "camera.hpp"
#include "mathematics/utility/constants.hpp"

#include <math.h>

using namespace mpl::graphics;
using namespace mpl::math;

Camera::Camera(Vector3 origin, Vector3 target, Vector3 world_up, double vertical_fov, double aspect_ratio) :
	m_origin(0.0),
	m_lower_left_corner(0.0),
	m_horizontal(0.0),
	m_vertical(0.0)
{
	Vector3 local_up(0.0);
	Vector3 local_right(0.0);
	Vector3 local_forward(0.0);

	// Compute local camera axes
	local_forward = (target - origin).Normalized();
	local_right = local_forward.Cross(world_up).Normalized();
	local_up = local_right.Cross(local_forward);

	m_origin = origin;

	double theta = vertical_fov * PI / 180.0;
	double half_height = tan(theta / 2.0);
	double half_width = aspect_ratio * half_height;

	m_lower_left_corner = { -half_width, -half_height, -1.0 };
	m_lower_left_corner = origin - half_width * local_right - half_height * local_up + local_forward;

	m_horizontal = 2.0 * half_width * local_right;
	m_vertical = 2.0 * half_height * local_up;
}

Camera::~Camera()
{
}

Ray Camera::CreateRay(double screen_u, double screen_v) const
{
	return { m_origin, m_lower_left_corner + (screen_u * m_horizontal) + (screen_v * m_vertical) - m_origin };
}
