#include "graphics/intersection/hit_list.hpp"
#include "graphics/intersection/sphere.hpp"
#include "graphics/ray/camera.hpp"
#include "graphics/ray/ray.hpp"
#include "graphics/shading/sky_gradient.hpp"
#include "mathematics/vector/vector3.hpp"

#include <fstream>
#include <limits>
#include <random>

using namespace mpl::graphics;
using namespace mpl::math;

Vector3 CalculateColor(const Ray& ray, const HitList& scene)
{
	HitInfo hit_info;

	if (scene.IsHit(ray, hit_info, 0.0, std::numeric_limits<double>::max()))
	{
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
	unsigned int sample_count = 32;

	std::ofstream output_file("./output.ppm");

	output_file << "P3\n" << horizontal_resolution << " " << vertical_resolution << "\n255\n";

	Camera camera;

	HitList scene(2);
	Sphere small_sphere({ 0.0, 0.0, -1.0 }, 0.5);
	Sphere big_sphere({ 0.0, -100.5, -1.0 }, 100.0);

	// Save the objects in the hit list
	scene.AddObject(&small_sphere);
	scene.AddObject(&big_sphere);

	std::default_random_engine random_number_engine;
	std::uniform_real_distribution<double> random_number_distribution(0.0, 1.0);

	for (int j = vertical_resolution - 1; j >= 0; --j)
	{
		for (unsigned int i = 0; i < horizontal_resolution; ++i)
		{
			Vector3 output_color;

			for (unsigned int s = 0; s < sample_count; ++s)
			{
				double screen_u = (static_cast<double>(i) + random_number_distribution(random_number_engine)) / static_cast<double>(horizontal_resolution);
				double screen_v = (static_cast<double>(j) + random_number_distribution(random_number_engine)) / static_cast<double>(vertical_resolution);

				Ray ray = camera.CreateRay(screen_u, screen_v);
				output_color += CalculateColor(ray, scene);
			}

			// Anti-aliasing: average all samples
			output_color /= static_cast<double>(sample_count);

			unsigned int red_i		= static_cast<int>(255.99f * output_color.R());
			unsigned int green_i	= static_cast<int>(255.99f * output_color.G());
			unsigned int blue_i		= static_cast<int>(255.99f * output_color.B());

			output_file << red_i << " " << green_i << " " << blue_i << "\n";
		}
	}

	return 0;
}
