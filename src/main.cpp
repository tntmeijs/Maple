#include "graphics/intersection/hit_list.hpp"
#include "graphics/intersection/sphere.hpp"
#include "graphics/ray/camera.hpp"
#include "graphics/ray/ray.hpp"
#include "graphics/shading/materials/lambertian.hpp"
#include "graphics/shading/materials/metallic.hpp"
#include "graphics/shading/sky_gradient.hpp"
#include "mathematics/utility/constants.hpp"
#include "mathematics/utility/indexing.hpp"
#include "mathematics/utility/point_on_unit_sphere.hpp"
#include "mathematics/vector/vector3.hpp"

#include <cmath>
#include <fstream>
#include <limits>
#include <string_view>
#include <vector>

using namespace mpl::graphics;
using namespace mpl::math;

/**
 * Calculate the color of the ray
 *
 * @param	ray				ray to evaluate
 * @param	scene			scene the ray should check against
 * @param	current_bounce	how many bounces this ray has performed
 * @param	max_bounces		maximum number of times this ray can bounce around
 *
 * @return	the final color of the ray after passing through the scene
 */
Vector3 CalculateColor(
	const Ray& ray,
	const HitList& scene,
	std::uint32_t current_bounce,
	std::uint32_t max_bounces)
{
	HitInfo hit_info;
	
	// t_min Is 0.001 to get rid of some of the shadow acne, essentially ignoring hits very close to zero
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
	
	//#TODO: Sky sphere
	// If the rays did not do anything, return the sky color
	return SkyGradient(ray);
}

/**
 * Perform gamma correction on the input color
 *
 * @param	color	color to apply gamma correction on
 * @param	gamma	gamma value used to correct the color
 *
 * @return	gamma corrected color
 */
Vector3 CalculateCorrectedGamma(const Vector3 color, double gamma)
{
	double corrected_r = pow(color.R(), 1.0 / gamma);
	double corrected_g = pow(color.G(), 1.0 / gamma);
	double corrected_b = pow(color.B(), 1.0 / gamma);

	return { corrected_r, corrected_g, corrected_b };
}

/**
 * Trace rays from the camera into the scene using the specified screen-space
 * pixel coordinates.
 *
 * @param	scene				scene to render
 * @param	camera				camera used to render the scene
 * @param	start_x				horizontal pixel position to start rendering from
 * @param	start_y				vertical pixel position to start rendering from
 * @param	end_x				horizontal pixel position to stop rendering at
 * @param	end_y				vertical pixel position to stop rendering at
 * @param	samples_per_pixel	number of rays to fire per pixel
 * @param	output_size_x		horizontal resolution of the output image
 * @param	output_size_y		vertical resolution of the output image
 * @param	bounces_per_ray		number of bounces performed per ray
 * @param	gamma				value to use for gamma correction
 *
 * @return	array of colors, each entry corresponds to one pixel in the image
 */
std::vector<Vector3> TraceRays(
	const HitList& scene,
	const Camera& camera,
	std::uint32_t start_x,
	std::uint32_t start_y,
	std::uint32_t end_x,
	std::uint32_t end_y,
	std::uint32_t samples_per_pixel,
	std::uint32_t output_size_x,
	std::uint32_t output_size_y,
	std::uint32_t bounces_per_ray,
	double gamma)
{
	std::vector<Vector3> pixel_array(static_cast<std::uint64_t>(end_x - start_x) * static_cast<std::uint64_t>(end_y - start_y));
	std::uniform_real_distribution<double> range(0.0, 1.0);

	for (std::uint32_t j = start_y; j < end_y; ++j)
	{
		for (std::uint32_t i = start_x; i < end_x; ++i)
		{
			// Color of this pixel
			Vector3 output_color;

			// Anti-aliasing: send multiple samples per pixel
			for (std::uint32_t s = 0; s < samples_per_pixel; ++s)
			{
				double screen_u = (static_cast<double>(i) + range(MAPLE_DEFAULT_RANDOM_ENGINE)) / static_cast<double>(output_size_x);
				double screen_v = (static_cast<double>(j) + range(MAPLE_DEFAULT_RANDOM_ENGINE)) / static_cast<double>(output_size_y);

				Ray ray = camera.CreateRay(screen_u, screen_v);
				output_color += CalculateColor(ray, scene, 0, 5);
			}

			// Anti-aliasing: average all samples
			output_color /= static_cast<double>(samples_per_pixel);

			// Gamma-correction
			output_color = CalculateCorrectedGamma(output_color, gamma);

			// Save the color, index a 1D array as a 2D array
			pixel_array[Index2DTo1D(j, i, end_x - start_x)] = output_color;
		}
	}

	return pixel_array;
}

/**
 * Output the pixel data to a PPM file
 *
 * @param	file			path to the output file with file extension
 * @param	pixels			raw pixel data
 * @param	output_size_x	horizontal image resolution
 * @param	output_size_y	vertical image resolution
 */
void WritePixelsToPPM(
	std::string_view file,
	const std::vector<Vector3> pixels,
	std::uint32_t output_size_x,
	std::uint32_t output_size_y)
{
	std::ofstream output_file("./output.ppm");

	// Write the PPM header
	output_file << "P3\n" << output_size_x << " " << output_size_y << "\n255\n";

	// Loop through the image data but flip the vertical coordinate to ensure
	// that the scene is not upside-down.
	for (std::int32_t j = output_size_y - 1; j >= 0; --j)
	{
		for (std::uint32_t i = 0; i < output_size_x; ++i)
		{
			Vector3 pixel = pixels[Index2DTo1D(j, i, output_size_x)];

			// Convert from floating-point value to an 8-bit integer value
			std::uint32_t red_255 = static_cast<int>(255.99f * pixel.R());
			std::uint32_t green_255 = static_cast<int>(255.99f * pixel.G());
			std::uint32_t blue_255 = static_cast<int>(255.99f * pixel.B());

			// Write to the PPM file
			output_file << red_255 << " " << green_255 << " " << blue_255 << "\n";
		}
	}
}

int main(int argc, char* argv[])
{
	constexpr std::uint32_t horizontal_resolution = 800;
	constexpr std::uint32_t vertical_resolution = 400;
	constexpr std::uint32_t per_pixel_sample_count = 16;
	constexpr std::uint32_t ray_bounce_count = 5;
	constexpr double vertical_fov_degrees = 45.0;
	constexpr double aspect_ratio = static_cast<double>(horizontal_resolution) / static_cast<double>(vertical_resolution);
	constexpr double gamma = 2.2;

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

	// Render the scene
	std::vector<Vector3> raw_image_data = TraceRays(
		scene,
		camera,
		0,
		0,
		horizontal_resolution,
		vertical_resolution,
		per_pixel_sample_count,
		horizontal_resolution,
		vertical_resolution,
		ray_bounce_count,
		gamma);

	// Write the pixel data to disk
	WritePixelsToPPM("./output.ppm", raw_image_data, horizontal_resolution, vertical_resolution);

	return 0;
}
