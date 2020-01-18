#include "skysphere.hpp"
#include "mathematics/vector/vector3.hpp"

using namespace mpl::graphics;
using namespace mpl::math;

SkySphere::SkySphere()
{
}

SkySphere::~SkySphere()
{
}

bool SkySphere::Create(std::string_view texture)
{
	return false;
}

Vector3 SkySphere::Sample(const Vector3& direction) const
{
	return Vector3();
}
