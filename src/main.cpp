#include <fstream>

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
			float red	= static_cast<float>(i) / static_cast<float>(horizontal_resolution);
			float green	= static_cast<float>(j) / static_cast<float>(vertical_resolution);
			float blue	= 0.2f;

			unsigned int red_i		= static_cast<int>(255.99f * red);
			unsigned int green_i	= static_cast<int>(255.99f * green);
			unsigned int blue_i		= static_cast<int>(255.99f * blue);

			output_file << red_i << " " << green_i << " " << blue_i << "\n";
		}
	}

	return 0;
}
