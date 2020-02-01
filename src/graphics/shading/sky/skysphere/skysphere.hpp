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

		/**
		 * If the image data has not been freed yet, it will be freed
		 * automatically. It is better to do this manually.
		 */
		~SkySphere();

		/**
		 * Load a new texture from disk as the sky sphere.
		 * An HDR texture works best.
		 * 
		 * @param	texture		path to the texture, including file extension
		 * 
		 * @return	true when the operation succeeds
		 */
		bool Create(std::string_view texture);

		/**
		 * Sample from the skysphere using the specified direction.
		 * The direction is assumed to be normalized already.
		 * Formula used:
		 * https://en.wikipedia.org/wiki/UV_mapping
		 * 
		 * @param	direction from the center of the sphere to the edge
		 * 
		 * @return	final color of the sample
		 */
		math::Vector3 Sample(const math::Vector3& direction) const;

		/**
		 * Free the allocated image memory.
		 */
		void Destroy();

	private:
		std::int32_t m_width;
		std::int32_t m_height;

		float* m_data;

		bool m_destroyed;
	};
}

#endif //! MAPLE_SKYSPHERE_HPP
