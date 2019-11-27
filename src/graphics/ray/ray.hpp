#ifndef MAPLE_RAY_HPP
#define MAPLE_RAY_HPP

#include "mathematics/vector/vector3.hpp"

namespace mpl::graphics
{
	/**
	 * Class that makes ray calculations easier
	 */
	class Ray
	{
	public:
		/** Create a new ray with an origin at (0, 0, 0) and a direction of (0, 0, -1) */
		Ray();

		/** Create a new ray with an origin and a direction */
		Ray(const math::Vector3& origin, const math::Vector3& direction);

		~Ray();

		/** Get the origin of the ray (start position) */
		const math::Vector3& Origin() const;

		/** Get the direction of the ray */
		const math::Vector3& Direction() const;

		/** Get a point along the ray's direction */
		const math::Vector3 PointAt(double distance) const;

		/** Perfectly reflects the ray's direction */
		math::Vector3 Reflect(const Ray& ray, const math::Vector3& normal) const;

	private:
		// Start position of the ray
		math::Vector3 m_origin;

		// Direction of the ray
		math::Vector3 m_direction;
	};
}

#endif //! MAPLE_RAY_HPP
