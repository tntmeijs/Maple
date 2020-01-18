#ifndef MAPLE_SKYSPHERE_HPP
#define MAPLE_SKYSPHERE_HPP

#include <string_view>

namespace mpl::math
{
	class Vector3;
}

namespace mpl::graphics
{
	/**
	 * Allows the application to sample from a spherical texture
	 */
	class SkySphere
	{
	public:
		SkySphere();
		~SkySphere();

		/**
		 * Load a new texture from disk as the sky sphere.
		 * 
		 * @param	texture		path to the texture, including file extension
		 * 
		 * @return	true when the operation succeeds
		 */
		bool Create(std::string_view texture);

		/**
		 * Sample from the skysphere using the specified direction.
		 * 
		 * @param	direction from the center of the sphere to the edge
		 * 
		 * @return	final color of the sample
		 */
		math::Vector3 Sample(const math::Vector3& direction) const;

	private:
	};
}

#endif //! MAPLE_SKYSPHERE_HPP
