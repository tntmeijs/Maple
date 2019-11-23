#include "mathematics/vector/vector3.hpp"

#include <fstream>

using namespace mpl::math;

int main(int argc, char* argv[])
{
	unsigned int horizontal_resolution = 960;
	unsigned int vertical_resolution = 540;

	std::ofstream output_file("./output.ppm");

	output_file << "P3\n" << horizontal_resolution << " " << vertical_resolution << "\n255\n";

	for (int j = vertical_resolution - 1; j >= 0; --j)
	{
		for (unsigned int i = 0; i < horizontal_resolution; ++i)
		{
			Vector3 color(static_cast<float>(i) / static_cast<float>(horizontal_resolution), static_cast<float>(j) / static_cast<float>(vertical_resolution), 0.2);

			unsigned int red_i		= static_cast<int>(255.99f * color.R());
			unsigned int green_i	= static_cast<int>(255.99f * color.G());
			unsigned int blue_i		= static_cast<int>(255.99f * color.B());

			output_file << red_i << " " << green_i << " " << blue_i << "\n";
		}
	}

	return 0;
}
