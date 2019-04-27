#ifndef FLAME_FUNCTOR_H
#define FLAME_FUNCTOR_H

#include "Buffer2D.hpp"
#include "Color.hpp"

#include <vector>

bool rand_bool();
int rand_int(const int min, const int max);
float rand_float(const float min, const float max);
int binary_search(const std::vector<float>& cumulated_values, float random_value);

namespace IFS{
	struct Function{
		float a;
		float b;
		float c;
		float d;
		float e;
		float f;

		void operator()(float& x, float& y) const;
	};

	namespace Library{
		// std::vector<FunctionType>
		//		functions with uniform probabilities
		std::vector<Function> serpinski_gasket();
		std::vector<Function> levy_curve();
		std::vector<Function> heighway_dragon_cartesian();

		// std::vector<std::pair<Function, float>>
		//		functions with provided non-uniform probabilities
		std::vector<std::pair<Function, float>> barnsley_fern();
		std::vector<std::pair<Function, float>> barnsley_fern_mutated();

		// std::pair<std::vector<Function>, std::vector<std::pair<float, float>>>
		//		functions with uniform probabilities and a provided initial sample set
		std::pair<std::vector<Function>, std::vector<std::pair<float, float>>> heighway_dragon_complex();
		std::pair<std::vector<Function>, std::vector<std::pair<float, float>>> twin_dragon_complex();
		std::pair<std::vector<Function>, std::vector<std::pair<float, float>>> ter_dragon_complex();
	}

	// runs a chaos game with a set of functions with uniform probabilities
	// returns a view of the density of points in a bi-unit square scaled by
	// /scale/ and centered at (/center_x/, /center_y/)
	template<typename FunctionType>
	Buffer2D<unsigned int> solve(const std::vector<FunctionType>& func,
			const unsigned int pixel_resolution,
			const unsigned int sample_per_pixel,
			const unsigned int iterations_per_sample = 20,
			const float center_x = 0.f, const float center_y = 0.f,
			const float scale = 1.f);

	// runs a chaos game with a set of functions with different probabilities
	// returns a view of the density of points in a bi-unit square scaled by
	// /scale/ and centered at (/center_x/, /center_y/)
	template<typename FunctionType>
	Buffer2D<unsigned int> solve(const std::vector<std::pair<FunctionType, float>>& func_prob,
			const unsigned int pixel_resolution,
			const unsigned int sample_per_pixel,
			const unsigned int iterations_per_sample = 20,
			const float center_x = 0.f, const float center_y = 0.f,
			const float scale = 1.f);

	// runs a chaos game with a set of functions with uniform probabilities
	// with the provided starting coordinates
	// returns a view of the density of points in a bi-unit square scaled by
	// 	/scale/ and centedred at (/center_x/, /center_y/)
	template<typename FunctionType>
	Buffer2D<unsigned int> solve_complex(
		const std::pair<std::vector<FunctionType>, std::vector<std::pair<float, float>>>& func_sample,
		const unsigned int pixel_resolution,
		const unsigned int iterations_per_sample = 20,
		const float center_x = 0.f, const float center_y = 0.f,
		const float scale = 1.f);

	Buffer2D<RGB> render(const Buffer2D<unsigned int>& src,
			const ColorMap& colormap = Palette::viridis());
	Buffer2D<RGB> binary_render(const Buffer2D<unsigned int>& src);
	Buffer2D<RGB> log_render(const Buffer2D<unsigned int>& src,
			const ColorMap& colormap = Palette::viridis());
}

#include "FlameFunctor.inl"

#endif
