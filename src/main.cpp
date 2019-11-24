#include "graphics/intersection/hit_list.hpp"
#include "graphics/intersection/sphere.hpp"
#include "graphics/ray/ray.hpp"
#include "graphics/shading/sky_gradient.hpp"
#include "mathematics/vector/vector3.hpp"

#include <fstream>
#include <limits>

using namespace mpl::graphics;
using namespace mpl::math;

Vector3 CalculateColor(const Ray& ray, const HitList& scene)
{
	HitInfo hit_info;

	if (scene.IsHit(ray, hit_info, 0.0, std::numeric_limits<double>::max()))
	{
		hit_info.normal.Normalize();
		return 0.5 * Vector3(hit_info.normal.X() + 1.0, hit_info.normal.Y() + 1.0, hit_info.normal.Z() + 1.0);
	}
	else
	{
		return SkyGradient(ray);
	}
}

int main(int argc, char* argv[])
{
	unsigned int horizontal_resolution = 400;
	unsigned int vertical_resolution = 200;

	std::ofstream output_file("./output.ppm");

	output_file << "P3\n" << horizontal_resolution << " " << vertical_resolution << "\n255\n";

	Vector3 lower_left_corner(-2.0, -1.0, -1.0);
	Vector3 horizontal(4.0, 0.0, 0.0);
	Vector3 vertical(0.0, 2.0, 0.0);
	Vector3 origin;

	HitList scene(2);
	Sphere small_sphere({ 0.0, 0.0, -1.0 }, 0.5);
	Sphere big_sphere({ 0.0, -100.5, -1.0 }, 100.0);

	// Save the objects in the hit list
	scene.AddObject(&small_sphere);
	scene.AddObject(&big_sphere);

	for (int j = vertical_resolution - 1; j >= 0; --j)
	{
		for (unsigned int i = 0; i < horizontal_resolution; ++i)
		{
			double screen_u = static_cast<double>(i) / static_cast<double>(horizontal_resolution);
			double screen_v = static_cast<double>(j) / static_cast<double>(vertical_resolution);

			Ray ray(origin, lower_left_corner + (screen_u * horizontal) + (screen_v * vertical));
			Vector3 output_color = CalculateColor(ray, scene);

			unsigned int red_i		= static_cast<int>(255.99f * output_color.R());
			unsigned int green_i	= static_cast<int>(255.99f * output_color.G());
			unsigned int blue_i		= static_cast<int>(255.99f * output_color.B());

			output_file << red_i << " " << green_i << " " << blue_i << "\n";
		}
	}

	return 0;
}
