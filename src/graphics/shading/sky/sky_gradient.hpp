#ifndef MAPLE_SKY_GRADIENT_HPP
#define MAPLE_SKY_GRADIENT_HPP

#include "graphics/ray/ray.hpp"
#include "mathematics/vector/vector3.hpp"

namespace mpl::graphics
{
	/** Return a blue gradient */
	inline math::Vector3 SkyGradient(const Ray& ray)
	{
		math::Vector3 direction = ray.Direction().Normalized();

		// Scale to (0.0 < t < 1.0) range
		double step = 0.5 * (direction.Y() + 1.0);

		math::Vector3 white(1.0, 1.0, 1.0);
		math::Vector3 blue(0.5, 0.7, 1.0);

		// Linearly interpolate the color using the vertical change of the ray's direction
		return white.LerpTo(blue, step);
	}
}

#endif //! MAPLE_SKY_GRADIENT_HPP
