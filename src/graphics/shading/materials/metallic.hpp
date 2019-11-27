#ifndef MAPLE_METALLIC_HPP
#define MAPLE_METALLIC_HPP

#include "graphics/intersection/hitable_object.hpp"
#include "graphics/shading/materials/material.hpp"
#include "mathematics/utility/point_on_unit_sphere.hpp"
#include "mathematics/vector/vector3.hpp"

namespace mpl::graphics
{
	/**
	 * Simple metallic material
	 */
	class MetallicMaterial final : public Material
	{
	public:
		/**
		 * Create a new Lambertian material with the specified albedo color and roughness
		 */
		MetallicMaterial(const math::Vector3& albedo, double roughness) :
			m_albedo(albedo),
			m_roughness(roughness)
		{}

		~MetallicMaterial() {}

		/**
		 * A metallic material will simply reflect the ray
		 */
		bool Scatter(const Ray& in_ray, const HitInfo& hit_info, math::Vector3& attenuation, Ray& out_ray) const override
		{
			math::Vector3 reflection = in_ray.Reflect(in_ray, hit_info.normal);
			out_ray = Ray(hit_info.position, reflection + m_roughness * math::GenerateRandomPointOnUnitSphere());
			attenuation = m_albedo;
			return (reflection.Dot(hit_info.normal) > 0.0);
		}

	private:
		math::Vector3 m_albedo;
		double m_roughness;
	};
}

#endif //! MAPLE_METALLIC_HPP
