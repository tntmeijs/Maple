#ifndef MAPLE_POINT_ON_UNIT_SPHERE_HPP
#define MAPLE_POINT_ON_UNIT_SPHERE_HPP

#include "mathematics/vector/vector3.hpp"

#include <random>

namespace mpl::math
{
	static std::default_random_engine MAPLE_DEFAULT_RANDOM_ENGINE;

	/**
	 * Generate a random point on a unit sphere
	 */
	inline Vector3 GenerateRandomPointOnUnitSphere()
	{
		double x = 0.0;
		double y = 0.0;
		double z = 0.0;

		Vector3 point;
		std::uniform_real_distribution<double> distribution(-1.0, 1.0);

		// Ensure that the components are not all zero
		do
		{
			point.X(distribution(MAPLE_DEFAULT_RANDOM_ENGINE));
			point.Y(distribution(MAPLE_DEFAULT_RANDOM_ENGINE));
			point.Z(distribution(MAPLE_DEFAULT_RANDOM_ENGINE));

		} while (point.LengthSquared() >= 1.0);

		return point;
	}
}

#endif //! MAPLE_POINT_ON_UNIT_SPHERE_HPP
