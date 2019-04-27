#ifndef COLOR_H
#define COLOR_H

#include <vector>

struct RGB{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

struct fRGB{
	float r;
	float g;
	float b;
};

struct ColorMap{
	ColorMap(const std::vector<fRGB>& i_color_values);

	RGB sample(float value) const;

	std::vector<fRGB> color_values;
};

namespace Palette{
	ColorMap viridis();
}


#endif
