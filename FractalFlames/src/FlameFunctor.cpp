#include "FlameFunctor.hpp"

#include <cmath>
#include <random>
#include <algorithm>

bool rand_bool(){
	static std::random_device seeder;
	static std::mt19937 source(seeder());
	static std::bernoulli_distribution distrib(0.5);

	return distrib(source);
}

int rand_int(const int min, const int max){
	static std::random_device seeder;
	static std::mt19937 source(seeder());
	std::uniform_int_distribution<int> distrib(min, max);

	return distrib(source);
}

float rand_float(const float min, const float max){
	static std::random_device seeder;
	static std::mt19937 source(seeder());
	std::uniform_real_distribution<float> distrib(min, max);

	return distrib(source);
}

int binary_search(const std::vector<float>& cumulated_values, float random_value){
	int min_pos = 0;
	int max_pos = cumulated_values.size() - 1;

	while((max_pos - min_pos) > 1){
		int middle_pos = (min_pos + max_pos) / 2;

		if(cumulated_values[middle_pos] <= random_value){
			min_pos = middle_pos;

		}else{
			max_pos = middle_pos;
		}
	}

	return min_pos;
}

namespace IFS{
	void Function::operator()(float& x, float& y) const{
		float temp_x = x;

		x = a * x + b * y + c;
		y = d * temp_x + e * y + f;
	}

	namespace Library{
		std::vector<Function> serpinski_gasket(){
			return {{0.5f, 0.f, 0.f,  0.f, 0.5f, 0.f},
				{0.5f, 0.f, 0.5f,  0.f, 0.5f, 0.f},
				{0.5f, 0.f, 0.f,  0.f, 0.5f, 0.5f}};
		}

		std::vector<std::pair<Function, float>> barnsley_fern(){
			return {{{0.f, 0.f, 0.f, 0.f, 0.16f, 0.f}, 0.01},
					{{0.85f, 0.04f, 0.f, -0.04f, 0.85f, 1.6f}, 0.85},
					{{0.2f, -0.26f, 0.f, 0.23f, 0.22f, 1.6f}, 0.07},
					{{-0.15f, 0.28f, 0.f, 0.26f, 0.24f, 0.44f}, 0.07}};
		}

		std::vector<std::pair<Function, float>> barnsley_fern_mutated(){
			return {{{0.f, 0.f, 0.f, 0.f, 0.25f, -0.4f}, 0.02},
					{{0.95f, 0.005f, -0.0002f, -0.005f, 0.93f, 0.5f}, 0.84},
					{{0.035f, -0.2f, -0.09f, 0.16f, 0.04f, 0.02f}, 0.07},
					{{-0.04f, 0.2f, 0.083f, 0.16f, 0.04f, 0.12f}, 0.07}};
		}

		std::vector<Function> levy_curve(){
			return {{0.5f, -0.5f, 0.f, 0.5f, 0.5f, 0.f},
					{0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f}};
		}

		std::vector<Function> heighway_dragon_cartesian(){
			float mul = 1.f / std::sqrt(2.f);
			float rad45 = 45.f * 2.f * M_PI / 360.f;
			float rad135 = 135.f * 2.f * M_PI / 360.f;

			return {{mul * std::cos(rad45), - mul * std::sin(rad45), 0.f, mul * std::sin(rad45), mul * std::cos(rad45), 0.f},
					{mul * std::cos(rad135), - mul * std::sin(rad135), 1.f, mul * std::sin(rad135), mul * std::cos(rad135), 0.f}};
		}

		std::pair<std::vector<Function>, std::vector<std::pair<float, float>>> heighway_dragon_complex(){
			return {{{0.5f, -0.5f, 0.f, 0.5f, 0.5f, 0.f},
					{-0.5f, -0.5f, 1.f, 0.5f, -0.5f, 0.f}},

					{{0.f, 0.f}, {1.f, 0.f}}};
		}

		std::pair<std::vector<Function>, std::vector<std::pair<float, float>>> twin_dragon_complex(){
			return {{{0.5f, -0.5f, 0.f, 0.5f, 0.5f, 0.f},
					{0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f}},

					{{0.f, 0.f}, {1.f, 0.f}}};
		}

		std::pair<std::vector<Function>, std::vector<std::pair<float, float>>> ter_dragon_complex(){
			float mulA = 1.f / (2.f * std::sqrt(3.f));
			float mulB = 1.f / std::sqrt(3.f);

			return {{{0.5f, mulA, 0.f, - mulA, 0.5f, 0.f},
					{0.f, - mulB, 0.5f, mulB, 0.f, - mulA},
					{0.5f, mulA, 0.5f, - mulA, 0.5f, mulA}},

					{{0.f, 0.f}, {1.f, 0.f}}};
		}
	}

	Buffer2D<RGB> render(const Buffer2D<unsigned int>& src,
		const ColorMap& colormap){

		Buffer2D<float> mapping(src);

		float max_value = mapping.max();
		for(unsigned int ival = 0; ival != mapping.sizeX * mapping.sizeY; ++ival){
			mapping.data[ival] /= max_value;
		}

		Buffer2D<RGB> render(src.sizeX, src.sizeY);
		for(unsigned int ival = 0; ival != render.sizeX * render.sizeY; ++ival){
			render.data[ival] = colormap.sample(mapping.data[ival]);
		}

		return render;
	}

	Buffer2D<RGB> binary_render(const Buffer2D<unsigned int>& src){
		Buffer2D<RGB> render(src.sizeX, src.sizeY);
		for(unsigned int ival = 0; ival != render.sizeX * render.sizeY; ++ival){
			if(src.data[ival] > 0){
				render.data[ival].r = (char)255;
				render.data[ival].g = (char)255;
				render.data[ival].b = (char)255;

			}else{
				render.data[ival].r = (char)50;
				render.data[ival].g = (char)50;
				render.data[ival].b = (char)50;

			}
		}

		return render;
	}

	Buffer2D<RGB> log_render(const Buffer2D<unsigned int>& src,
		const ColorMap& colormap){

		Buffer2D<float> mapping(src);

		for(unsigned int ival = 0; ival != mapping.sizeX * mapping.sizeY; ++ival){
			mapping.data[ival] = std::log10(mapping.data[ival]);
		}

		float max_value = mapping.max();
		for(unsigned int ival = 0; ival != mapping.sizeX * mapping.sizeY; ++ival){
			mapping.data[ival] /= max_value;
		}

		Buffer2D<RGB> render(src.sizeX, src.sizeY);
		for(unsigned int ival = 0; ival != render.sizeX * render.sizeY; ++ival){
			render.data[ival] = colormap.sample(mapping.data[ival]);
		}

		return render;
	}
}
