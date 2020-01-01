#ifndef MAPLE_INDEXING_HPP
#define MAPLE_INDEXING_HPP

namespace mpl::math
{
	/**
	 * Index a 1D array as a 2D array
	 *
	 * @param	row		2D index row component
	 * @param	column	2D index column component
	 * @param	width	width of a single row
	 *
	 * @return	index into the 1D array
	 */
	std::uint32_t Index2DTo1D(std::uint32_t row, std::uint32_t column, std::uint32_t width)
	{
		return ((row * width) + column);
	}
}

#endif //! MAPLE_INDEXING_HPP
