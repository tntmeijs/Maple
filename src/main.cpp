#include "graphics/ray/ray.hpp"
#include "graphics/shading/sky_gradient.hpp"
#include "mathematics/vector/vector3.hpp"

#include <fstream>

using namespace mpl::graphics;
using namespace mpl::math;

double HitSphere(const Vector3& center, double radius, const Ray& ray)
{
	Vector3 origin_center = ray.Origin() - center;

	// ABC formula
	double a = ray.Direction().Dot(ray.Direction());
	double b = 2.0 * origin_center.Dot(ray.Direction());
	double c = origin_center.Dot(origin_center) - (radius * radius);
	double d = (b * b) - (4.0 * a * c);
	
	if (d < 0.0)
	{
		return -1.0;
	}
	else
	{
		return ((-b -sqrt(d)) / (2.0 * a));
	}
}

int main(int argc, char* argv[])
{
	unsigned int horizontal_resolution = 200;
	unsigned int vertical_resolution = 100;

	std::ofstream output_file("./output.ppm");

	output_file << "P3\n" << horizontal_resolution << " " << vertical_resolution << "\n255\n";

	Vector3 lower_left_corner(-2.0, -1.0, -1.0);
	Vector3 horizontal(4.0, 0.0, 0.0);
	Vector3 vertical(0.0, 2.0, 0.0);
	Vector3 origin;
	
	Vector3 sphere_position(0.0, 0.0, -1.0);

	for (int j = vertical_resolution - 1; j >= 0; --j)
	{
		for (unsigned int i = 0; i < horizontal_resolution; ++i)
		{
			double screen_u = static_cast<double>(i) / static_cast<double>(horizontal_resolution);
			double screen_v = static_cast<double>(j) / static_cast<double>(vertical_resolution);

			Ray ray(origin, lower_left_corner + (screen_u * horizontal) + (screen_v * vertical));
			Vector3 output_color;

			double t = HitSphere(sphere_position, 0.5, ray);
			if (t > 0.0)
			{
				Vector3 normal = ray.PointAt(t) - sphere_position;
				normal.Normalize();
				
				// Convert from (-1, 1) range to (0, 1)
				output_color = (Vector3(normal.X() + 1.0, normal.Y() + 1.0, normal.Z() + 1.0) * 0.5);
			}
			else
			{
				output_color = SkyGradient(ray);
			}

			unsigned int red_i		= static_cast<int>(255.99f * output_color.R());
			unsigned int green_i	= static_cast<int>(255.99f * output_color.G());
			unsigned int blue_i		= static_cast<int>(255.99f * output_color.B());

			output_file << red_i << " " << green_i << " " << blue_i << "\n";
		}
	}

	return 0;
}
