#ifndef MAPLE_LITERALS_HPP
#define MAPLE_LITERALS_HPP

#include "constants.hpp"

namespace mpl::math
{
	/**
	 * Convert degrees to radians
	 */
	inline constexpr long double operator"" _DegToRad(long double degrees)
	{
		return degrees * (PI / 180.0);
	}

	/**
	 * Convert radians to degrees
	 */
	inline constexpr long double operator"" _RadToDeg(long double radians)
	{
		return radians * (180.0 / PI);
	}
}

#endif //! MAPLE_LITERALS_HPP
