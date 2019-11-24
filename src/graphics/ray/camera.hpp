#ifndef MAPLE_CAMERA_HPP
#define MAPLE_CAMERA_HPP

#include "mathematics/vector/vector3.hpp"
#include "ray.hpp"

namespace mpl::graphics
{
	/**
	 * Camera class that will handle the creation of rays using a certain camera set-up
	 */
	class Camera
	{
	public:
		/**
		 * Create a new camera
		 */
		Camera();
		~Camera();

		/**
		 * Create a ray that originates from the camera and goes through the specified screen-space coordinate (normalized range)
		 */
		Ray CreateRay(double screen_u, double screen_v) const;

	private:
		math::Vector3 m_origin;
		math::Vector3 m_lower_left_corner;
		math::Vector3 m_horizontal;
		math::Vector3 m_vertical;
	};
}

#endif //! MAPLE_CAMERA_HPP
