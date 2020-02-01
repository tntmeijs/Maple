#include "skysphere.hpp"
#include "mathematics/utility/constants.hpp"
#include "mathematics/utility/indexing.hpp"
#include "mathematics/utility/literals.hpp"
#include "mathematics/vector/vector3.hpp"
#include "thirdparty/stb/stb_image.h"

#include <cmath>

using namespace mpl::graphics;
using namespace mpl::math;

SkySphere::SkySphere() :
	m_width(0),
	m_height(0),
	m_data(nullptr),
	m_destroyed(false)
{
}

SkySphere::~SkySphere()
{
	if (!m_destroyed)
	{
		Destroy();
	}
}

bool SkySphere::Create(std::string_view texture)
{
	int channels;
	m_data = stbi_loadf(texture.data(), &m_width, &m_height, &channels, STBI_rgb);

	return (m_data != nullptr && channels == STBI_rgb) ? true : false;
}

Vector3 SkySphere::Sample(const Vector3& direction) const
{
	// Find the UV on a sphere
	double u = 0.5 + (atan2(direction.Z(), direction.X()) / (2.0 * PI));
	double v = 0.5 - (asin(direction.Y()) / PI);

	// Find the pixels closest to this UV location
	auto x = static_cast<std::uint32_t>(floor(u * static_cast<double>(m_width)));
	auto y = static_cast<std::uint32_t>(floor(v * static_cast<double>(m_height)));

	// Multiply by 3 to account for the three color components in the array
	std::uint64_t index = Index2DTo1D(y, x, m_width) * 3;

	double red		= m_data[index + 0];
	double green	= m_data[index + 1];
	double blue		= m_data[index + 2];

	return { red, green, blue };
}

void SkySphere::Destroy()
{
	m_destroyed = true;
	stbi_image_free(m_data);
}
