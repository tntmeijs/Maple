#ifndef MAPLE_SPHERE_HPP
#define MAPLE_SPHERE_HPP

#include "hitable_object.hpp"
#include "mathematics/vector/vector3.hpp"

namespace mpl::graphics
{
	// Forward declaration
	class Material;

	/**
	 * Compute ray intersections with spheres
	 */
	class Sphere : public HitableObject
	{
	public:
		/**
		 * Create a new sphere at position (0, 0, 0) with a radius of 1
		 */
		Sphere(const Material* material);

		/**
		 * Create a new sphere with a custom position and radius
		 */
		Sphere(const math::Vector3& position, double radius, const Material* const material);

		virtual ~Sphere();

		/**
		 * Ray-sphere intersection logic
		 */
		virtual bool IsHit(const Ray& ray, HitInfo& hit_info, double step_min_distance, double step_max_distance) const override;

	private:
		// Position of the sphere measured at the center
		math::Vector3 m_center;

		// Material assigned to this sphere
		const Material* m_assigned_material;

		double m_radius;
	};
}

#endif //! MAPLE_SPHERE_HPP
