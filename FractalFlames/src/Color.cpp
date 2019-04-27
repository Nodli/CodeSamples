#include "Color.hpp"

#include <cassert>

ColorMap::ColorMap(const std::vector<fRGB>& i_color_values){
	color_values = i_color_values;
}

RGB ColorMap::sample(float value) const{
	assert(color_values.size() > 0);

	if((value <= 0.f) || (color_values.size() == 1)){
		return {(unsigned char)(color_values[0].r * 255.f),
				(unsigned char)(color_values[0].g * 255.f),
				(unsigned char)(color_values[0].b * 255.f)};

	}else if(value >= 1.f){

		return {(unsigned char)(color_values[color_values.size() - 1].r * 255.f),
			(unsigned char)(color_values[color_values.size() - 1].g * 255.f),
			(unsigned char)(color_values[color_values.size() - 1].b * 255.f)};

	}else{
		float sample_coord = value * (color_values.size() - 1);

		unsigned int sample_index = sample_coord;
		float sample_interpolator = sample_coord - sample_index;
		float sample_complement = 1.f - sample_interpolator;

		return {(unsigned char)((color_values[sample_index].r * sample_complement
			+ color_values[sample_index].r * sample_interpolator) * 255.f),

			(unsigned char)((color_values[sample_index].g * sample_complement
			+ color_values[sample_index].g * sample_interpolator) * 255.f),

			(unsigned char)((color_values[sample_index].b * sample_complement
			+ color_values[sample_index].b * sample_interpolator) * 255.f)};
	}

	return {0, 0, 0};
}

#include "Palette.inl"
