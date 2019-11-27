#ifndef MAPLE_MATERIAL_HPP
#define MAPLE_MATERIAL_HPP

// Forward declarations
namespace mpl
{
	namespace math
	{
		class Vector3;
	}

	namespace graphics
	{
		class Ray;
		struct HitInfo;
	}
}

namespace mpl::graphics
{
	/**
	 * Abstract class that handles the way a material absorbs or reflects rays when hit
	 */
	class Material
	{
	public:
		Material() {}
		virtual ~Material() {}
		virtual bool Scatter(const Ray& in_ray, const HitInfo& hit_info, math::Vector3& attenuation, Ray& out_ray) const = 0;
	};
}

#endif //! MAPLE_MATERIAL_HPP
