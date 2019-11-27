#include "sphere.hpp"

#include <math.h>

using namespace mpl::graphics;
using namespace mpl::math;

mpl::graphics::Sphere::Sphere(const Material* const material) :
	m_center(0.0, 0.0, 0.0),
	m_assigned_material(material),
	m_radius(1.0)
{
}

Sphere::Sphere(const Vector3& position, double radius, const Material* const material) :
	m_center(position),
	m_radius(radius),
	m_assigned_material(material)
{
}

Sphere::~Sphere()
{
}

bool Sphere::IsHit(const Ray& ray, HitInfo& hit_info, double step_min_distance, double step_max_distance) const
{
	Vector3 origin_center = ray.Origin() - m_center;

	// ABC formula
	double a = ray.Direction().Dot(ray.Direction());
	double b = 2.0 * origin_center.Dot(ray.Direction());
	double c = origin_center.Dot(origin_center) - (m_radius * m_radius);
	double d = (b * b) - (4.0 * a * c);

	// If the ABC formula can be solved for this step, populate the "hit_info" structure
	auto TryToFillHitInfo = [&hit_info, &ray, this](const Vector3& center, double step, double step_min_distance, double step_max_distance) {
		if (step > step_min_distance && step < step_max_distance)
		{
			hit_info.step_distance = step;
			hit_info.position = ray.PointAt(step);
			hit_info.normal = (hit_info.position - center).Normalized();
			hit_info.material = this->m_assigned_material;
			return true;
		}

		return false;
	};

	// There are solutions for this formula
	if (d > 0.0)
	{
		// Try a negative solution to the ABC formula
		double step = ((-b - sqrt(d)) / (2.0 * a));
		if (TryToFillHitInfo(m_center, step, step_min_distance, step_max_distance))
		{
			return true;
		}

		// Try a positive solution to the ABC formula
		step = ((-b + sqrt(d)) / (2.0 * a));
		if (TryToFillHitInfo(m_center, step, step_min_distance, step_max_distance))
		{
			return true;
		}
	}

	// The ray did not hit the sphere
	return false;
}
