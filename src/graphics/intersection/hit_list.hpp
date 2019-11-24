#ifndef MAPLE_HIT_LIST_HPP
#define MAPLE_HIT_LIST_HPP

#include "hitable_object.hpp"

#include <cstddef>	// std::size_t
#include <vector>

namespace mpl::graphics
{
	/**
	 * Compute whether the ray hits any of the objects in the list
	 */
	class HitList : public HitableObject
	{
	public:
		/**
		 * Create an empty hit list
		 */
		HitList();

		/**
		 * Create an empty hit list, but preallocate memory to hold objects
		 */
		HitList(std::size_t size);

		virtual ~HitList();

		/**
		 * Add a new object to the list
		 */
		void AddObject(const HitableObject* const object);

		/**
		 * Did the ray hit any of the objects in the list?
		 */
		virtual bool IsHit(const Ray& ray, HitInfo& hit_info, double step_min_distance, double step_max_distance) const override;

	private:
		std::vector<const HitableObject*> m_list;
	};
}

#endif //! MAPLE_HIT_LIST_HPP
