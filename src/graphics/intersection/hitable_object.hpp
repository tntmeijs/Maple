#ifndef MAPLE_HITABLE_OBJECT_HPP
#define MAPLE_HITABLE_OBJECT_HPP

#include "graphics/ray/ray.hpp"
#include "mathematics/vector/vector3.hpp"

namespace mpl::graphics
{
	// Forward declaration
	class Material;

	/**
	 * Provides basic information about a hit
	 * - step distance
	 * - hit position
	 * - surface normal at the hit point
	 */
	struct HitInfo
	{
		HitInfo() :
			step_distance(0.0),
			position(0.0, 0.0, 0.0),
			normal(0.0, 0.0, 0.0),
			material(nullptr)
		{
		}

		double step_distance;
		math::Vector3 position;
		math::Vector3 normal;
		Material* material;
	};

	/**
	 * Abstract class that provides basic functionality for all objects that can be "hit" by a ray
	 */
	class HitableObject
	{
	public:
		HitableObject() {}
		virtual ~HitableObject() {}

		/**
		 * Did the ray intersection with this object?
		 */
		virtual bool IsHit(const Ray& ray, HitInfo& hit_info, double step_min_distance, double step_max_distance) const = 0;
	};
}

#endif //! MAPLE_HITABLE_OBJECT_HPP
