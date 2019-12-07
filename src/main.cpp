#include "graphics/intersection/hit_list.hpp"
#include "graphics/intersection/sphere.hpp"
#include "graphics/ray/camera.hpp"
#include "graphics/ray/ray.hpp"
#include "graphics/shading/materials/lambertian.hpp"
#include "graphics/shading/materials/metallic.hpp"
#include "graphics/shading/sky_gradient.hpp"
#include "mathematics/utility/point_on_unit_sphere.hpp"
#include "mathematics/vector/vector3.hpp"
#include "mathematics/utility/constants.hpp"

#include <fstream>
#include <limits>

using namespace mpl::graphics;
using namespace mpl::math;

Vector3 CalculateColor(const Ray& ray, const HitList& scene, unsigned int current_bounce, unsigned int max_bounces)
{
	HitInfo hit_info;
	
	// t_min is 0.001 to get rid of some of the shadow acne, essentially ignoring hits very close to zero
	if (scene.IsHit(ray, hit_info, 0.001, std::numeric_limits<double>::max()))
	{
		Ray scattered_ray;
		Vector3 attenuation;

		// Bounce the ray
		if (current_bounce++ < max_bounces)
		{
			// Scatter the material or simply do nothing if the ray is not going to scatter at all
			if (hit_info.material->Scatter(ray, hit_info, attenuation, scattered_ray))
			{
				return attenuation * CalculateColor(scattered_ray, scene, current_bounce, max_bounces);
			}
		}
	}
	
	// If the rays did not do anything, return the sky color
	return SkyGradient(ray);
}

int main(int argc, char* argv[])
{
	constexpr unsigned int horizontal_resolution = 800;
	constexpr unsigned int vertical_resolution = 400;
	constexpr unsigned int per_pixel_sample_count = 16;
	constexpr double vertical_fov_degrees = 45.0;
	constexpr double aspect_ratio = static_cast<double>(horizontal_resolution) / static_cast<double>(vertical_resolution);

	std::ofstream output_file("./output.ppm");

	output_file << "P3\n" << horizontal_resolution << " " << vertical_resolution << "\n255\n";

	Camera camera({ -2.0, 2.0, 1.0 }, { 0.0, 0.0, -1.0 }, { 0.0, 1.0, 0.0 }, vertical_fov_degrees, aspect_ratio);

	HitList scene(4);
	
	// Lambertian sphere
	Sphere sphere_0({ 0.0, 0.0, -1.0 }, 0.5, new LambertianMaterial({ 0.8, 0.3, 0.3 }));
	Sphere sphere_1({ 0.0, -100.5, -1.0 }, 100.0, new LambertianMaterial({ 0.8, 0.8, 0.0 }));

	// Metallic sphere
	Sphere sphere_2({ 1.0, 0.0, -1.0 }, 0.5, new MetallicMaterial({ 0.8, 0.6, 0.2 }, 0.3));
	Sphere sphere_3({ -1.0, 0.0, -1.0 }, 0.5, new MetallicMaterial({ 0.8, 0.8, 0.8 }, 1.0));

	// Save the objects in the hit list
	scene.AddObject(&sphere_0);
	scene.AddObject(&sphere_1);
	scene.AddObject(&sphere_2);
	scene.AddObject(&sphere_3);

	std::uniform_real_distribution<double> zero_to_one_range(0.0, 1.0);

	for (int j = vertical_resolution - 1; j >= 0; --j)
	{
		for (unsigned int i = 0; i < horizontal_resolution; ++i)
		{
			Vector3 output_color;

			for (unsigned int s = 0; s < per_pixel_sample_count; ++s)
			{
				double screen_u = (static_cast<double>(i) + zero_to_one_range(MAPLE_DEFAULT_RANDOM_ENGINE)) / static_cast<double>(horizontal_resolution);
				double screen_v = (static_cast<double>(j) + zero_to_one_range(MAPLE_DEFAULT_RANDOM_ENGINE)) / static_cast<double>(vertical_resolution);

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
