#ifndef MAPLE_LAMBERTIAN_HPP
#define MAPLE_LAMBERTIAN_HPP

#include "graphics/intersection/hitable_object.hpp"
#include "graphics/shading/materials/material.hpp"
#include "mathematics/utility/point_on_unit_sphere.hpp"
#include "mathematics/vector/vector3.hpp"

namespace mpl::graphics
{
	/**
	 * Simple Lambertian material
	 */
	class LambertianMaterial final : public Material
	{
	public:
		/**
		 * Create a new Lambertian material with the specified albedo color
		 */
		LambertianMaterial(const math::Vector3& albedo) :
			m_albedo(albedo)
		{}

		~LambertianMaterial() {}

		/**
		 * Either scatter always and attenuate by the surface's reflectance, or absorb the fraction 1-R of the rays
		 */
		bool Scatter(const Ray& in_ray, const HitInfo& hit_info, math::Vector3& attenuation, Ray& out_ray) const override
		{
			math::Vector3 target = hit_info.position + hit_info.normal + math::GenerateRandomPointOnUnitSphere();
			out_ray = Ray(hit_info.position, target - hit_info.position);
			attenuation = m_albedo;
			return true;
		}

	private:
		math::Vector3 m_albedo;
	};
}

#endif //! MAPLE_LAMBERTIAN_HPP
