#ifndef FLAME_FUNCTOR_INL
#define FLAME_FUNCTOR_INL

#include <iostream>

namespace IFS{

	template<typename FunctionType>
	Buffer2D<unsigned int> solve(const std::vector<FunctionType>& func,
			const unsigned int pixel_resolution,
			const unsigned int sample_per_pixel,
			const unsigned int iterations_per_sample,
			const float center_x, const float center_y,
			const float scale){

		// computing the view corner coordinates
		float min_x = center_x - scale;

		float min_y = center_y - scale;
		float max_y = center_y + scale;

		Buffer2D<unsigned int> solution(pixel_resolution, pixel_resolution);
		const float solution_dres = (2.f * scale) / pixel_resolution;

		// buffer origin is at the top left
		for(unsigned int iy = 0; iy != pixel_resolution; ++iy){
			for(unsigned int ix = 0; ix != pixel_resolution; ++ix){

				// bi-unit scaled square origin is at the bottom left
				const float pixel_x = min_x + ix * solution_dres;
				const float pixel_y = max_y - iy * solution_dres;

				for(unsigned int isample = 0; isample != sample_per_pixel; ++isample){

					// global coordinates of the sample located inside the initial pixel
					float sample_x = pixel_x + rand_float(0.f, 1.f) * solution_dres;
					float sample_y = pixel_y - rand_float(0.f, 1.f) * solution_dres;

					for(unsigned int iter = 0; iter != iterations_per_sample; ++iter){

						// pick and evaluate a random function
						const unsigned int ifunc = (unsigned int)rand_int(0, func.size() - 1);
						func[ifunc](sample_x, sample_y);

						const int sample_pixel_x = (int)((sample_x - min_x) / (2.f * scale) * pixel_resolution);
						const int sample_pixel_y = (int)((2 * scale - sample_y + min_y) / (2.f * scale) * pixel_resolution);

						// protection against non-contracting function set
						if((sample_pixel_x >= 0) && (sample_pixel_x < pixel_resolution)
								&& (sample_pixel_y >= 0) && (sample_pixel_y < pixel_resolution)){

							++solution(sample_pixel_x, sample_pixel_y);
						}
					}
				}
			}
		}

		return solution;
	}

	template<typename FunctionType>
	Buffer2D<unsigned int> solve(const std::vector<std::pair<FunctionType, float>>& func_prob,
			const unsigned int pixel_resolution,
			const unsigned int sample_per_pixel,
			const unsigned int iterations_per_sample,
			const float center_x, const float center_y,
			const float scale){

		// computing the view corner coordinates
		float min_x = center_x - scale;

		float min_y = center_y - scale;
		float max_y = center_y + scale;

		// building the probability distribution of the function
		std::vector<float> cumulated_weights(1, 0.f);
		cumulated_weights.reserve(func_prob.size() + 1);
		for(unsigned int ifunc = 0; ifunc != func_prob.size(); ++ifunc){
			cumulated_weights.push_back(cumulated_weights[ifunc] + func_prob[ifunc].second);
		}

		Buffer2D<unsigned int> solution(pixel_resolution, pixel_resolution);
		const float solution_dres = (2.f * scale) / pixel_resolution;

		// buffer oriring is at the top left
		for(unsigned int iy = 0; iy != pixel_resolution; ++iy){
			for(unsigned int ix = 0; ix != pixel_resolution; ++ix){

				// bi-unit scaled square origin is at the bottom left
				const float pixel_x = -1.f + ix * solution_dres;
				const float pixel_y = -1.f + iy * solution_dres;

				for(unsigned int isample = 0; isample != sample_per_pixel; ++isample){

					// global coordinates of the sample located inside the initial pixel
					float sample_x = pixel_x + rand_float(0.f, 1.f) * solution_dres;
					float sample_y = pixel_y + rand_float(0.f, 1.f) * solution_dres;

					for(unsigned int iter = 0; iter != iterations_per_sample; ++iter){

						// pick and evaluate a random function according to their probability
						float random_value = rand_float(0.f, cumulated_weights[cumulated_weights.size() - 1]);
						const unsigned int ifunc = (unsigned int)binary_search(cumulated_weights, random_value);
						func_prob[ifunc].first(sample_x, sample_y);

						const int sample_pixel_x = (int)((sample_x - min_x) / (2.f * scale) * pixel_resolution);
						const int sample_pixel_y = (int)((2 * scale - sample_y + min_y) / (2.f * scale) * pixel_resolution);

						// protection against non-contracting function set
						if((sample_pixel_x >= 0) && (sample_pixel_x < pixel_resolution)
								&& (sample_pixel_y >= 0) && (sample_pixel_y < pixel_resolution)){
							++solution(sample_pixel_x, sample_pixel_y);

						}
					}
				}
			}
		}

		return solution;
	}

	template<typename FunctionType>
	Buffer2D<unsigned int> solve_complex(
			const std::pair<std::vector<FunctionType>, std::vector<std::pair<float, float>>>& func_sample,
			const unsigned int pixel_resolution,
			const unsigned int iterations_per_sample,
			const float center_x, const float center_y,
			const float scale){

		// computing the view corner coordinates
		float min_x = center_x - scale;

		float min_y = center_y - scale;
		float max_y = center_y + scale;

		// buffer origin is at the top left
		Buffer2D<unsigned int> solution(pixel_resolution, pixel_resolution);

		std::vector<std::pair<float, float>> samples(func_sample.second);
		for(unsigned int iter = 0; iter != iterations_per_sample; ++iter){

			std::vector<std::pair<float, float>> new_samples;
			new_samples.reserve(func_sample.first.size() * samples.size());

			for(unsigned int ifunc = 0; ifunc != func_sample.first.size(); ++ifunc){
				for(unsigned isample = 0; isample != samples.size(); ++isample){

					// computing the new sample position
					float sample_x = samples[isample].first;
					float sample_y = samples[isample].second;
					func_sample.first[ifunc](sample_x, sample_y);

					// marking the sample in the solution
					const int sample_pixel_x = (int)((sample_x - min_x) / (2.f * scale) * pixel_resolution);
					const int sample_pixel_y = (int)((2 * scale - sample_y + min_y) / (2.f * scale) * pixel_resolution);

					// protection against non-contracting function set
					if((sample_pixel_x >= 0) && (sample_pixel_x < pixel_resolution)
							&& (sample_pixel_y >= 0) && (sample_pixel_y < pixel_resolution)){

						if(solution(sample_pixel_x, sample_pixel_y) == 0){
							solution(sample_pixel_x, sample_pixel_y) = iter + 1;
						}
					}

					new_samples.emplace_back(sample_x, sample_y);
				}
			}

			std::swap(samples, new_samples);
		}

		return solution;
	}
}

#endif
