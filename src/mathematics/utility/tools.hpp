#ifndef MAPLE_TOOLS_HPP
#define MAPLE_TOOLS_HPP

namespace mpl::math
{
	/**
	 * Clamp a value between a minimum and maximum value
	 * 
	 * @param			value the value that needs to be clamped
	 * @param minimum	lower bound to clamp to
	 * @param maximum	upper bound to clamp to
	 * @return			clamped value
	 */
	template<typename T>
	inline T Clamp(T value, T minimum, T maximum)
	{
		if (value < minimum)
		{
			return minimum;
		}
		else if (value > maximum)
		{
			return maximum;
		}
		else
		{
			return value;
		}
	}
}

#endif //! MAPLE_TOOLS_HPP
