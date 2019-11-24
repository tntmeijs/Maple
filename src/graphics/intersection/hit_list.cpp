#include "hit_list.hpp"

using namespace mpl::graphics;

HitList::HitList()
{
}

HitList::HitList(std::size_t size)
{
	m_list.reserve(size);
}

HitList::~HitList()
{
}

void HitList::AddObject(const HitableObject* const object)
{
	m_list.push_back(object);
}

bool HitList::IsHit(const Ray& ray, HitInfo& hit_info, double step_min_distance, double step_max_distance) const
{
	HitInfo temp_hit_info;
	bool hit_any_object = false;
	double closest_hit_step = step_max_distance;

	for (const HitableObject* const object : m_list)
	{
		if (object->IsHit(ray, temp_hit_info, step_min_distance, closest_hit_step))
		{
			hit_any_object = true;
			closest_hit_step = temp_hit_info.step_distance;
			hit_info = temp_hit_info;
		}
	}

	return hit_any_object;
}
