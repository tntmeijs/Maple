#include "graphics/intersection/hit_list.hpp"
#include "graphics/intersection/sphere.hpp"
#include "graphics/ray/camera.hpp"
#include "graphics/ray/ray.hpp"
#include "graphics/shading/sky_gradient.hpp"
#include "mathematics/vector/vector3.hpp"
#include "mathematics/utility/point_on_unit_sphere.hpp"

#include <fstream>
#include <limits>
#include <random>

using namespace mpl::graphics;
using namespace mpl::math;

std::default_random_engine generator;

Vector3 CalculateColor(const Ray& primary_ray, const HitList& scene, unsigned int current_bounce, unsigned int max_bounces)
{
	HitInfo hit_info;
	
	// t_min is 0.001 to get rid of some of the shadow acne, essentially ignoring hits very close to zero
	if (scene.IsHit(primary_ray, hit_info, 0.001, std::numeric_limits<double>::max()) && current_bounce < max_bounces)
	{
		++current_bounce;
		Vector3 secondary_ray_direction = hit_info.position + hit_info.normal + GenerateRandomPointOnUnitSphere(generator);

		// Absorb half the energy on each bounce
		return 0.5 * CalculateColor(Ray(hit_info.position, secondary_ray_direction - hit_info.position), scene, current_bounce, max_bounces);
	}
	else
	{
		return SkyGradient(primary_ray);
	}
}

int main(int argc, char* argv[])
{
	unsigned int horizontal_resolution = 800;
	unsigned int vertical_resolution = 400;
	unsigned int per_pixel_sample_count = 16;

	std::ofstream output_file("./output.ppm");

	output_file << "P3\n" << horizontal_resolution << " " << vertical_resolution << "\n255\n";

	Camera camera;

	HitList scene(2);
	Sphere small_sphere({ 0.0, 0.0, -1.0 }, 0.5);
	Sphere big_sphere({ 0.0, -100.5, -1.0 }, 100.0);

	// Save the objects in the hit list
	scene.AddObject(&small_sphere);
	scene.AddObject(&big_sphere);

	std::uniform_real_distribution<double> zero_to_one_range(0.0, 1.0);

	for (int j = vertical_resolution - 1; j >= 0; --j)
	{
		for (unsigned int i = 0; i < horizontal_resolution; ++i)
		{
			Vector3 output_color;

			for (unsigned int s = 0; s < per_pixel_sample_count; ++s)
			{
				double screen_u = (static_cast<double>(i) + zero_to_one_range(generator)) / static_cast<double>(horizontal_resolution);
				double screen_v = (static_cast<double>(j) + zero_to_one_range(generator)) / static_cast<double>(vertical_resolution);

				Ray ray = camera.CreateRay(screen_u, screen_v);
				output_color += CalculateColor(ray, scene, 0, 5);
			}

			// Anti-aliasing: average all samples
			output_color /= static_cast<double>(per_pixel_sample_count);

			// Gamma-correction
			output_color.R(sqrt(output_color.R()));
			output_color.G(sqrt(output_color.G()));
			output_color.B(sqrt(output_color.B()));

			unsigned int red_i		= static_cast<int>(255.99f * output_color.R());
			unsigned int green_i	= static_cast<int>(255.99f * output_color.G());
			unsigned int blue_i		= static_cast<int>(255.99f * output_color.B());

			output_file << red_i << " " << green_i << " " << blue_i << "\n";
		}
	}

	return 0;
}
