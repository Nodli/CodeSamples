#include <stdio.h>
#include <time.h>
#include <limits.h>

/*
Can you find two numbers that add to 16 ?

[1, 3, 5, 8, 12, 13, 22]

Source:
https://www.reddit.com/r/learnprogramming/comments/9vp1vv/an_interesting_problem_from_a_job_interview_at/

*/

bool naive_nsquare(int nb_values, int* values, int sum_value, int* output_couple){

	for(int iA = 0; iA != nb_values; ++iA){
		for(int iB = 0; iB != nb_values; ++iB){

			if((iA != iB) && ((values[iA] + values[iB]) == sum_value)){
				output_couple[0] = values[iA];
				output_couple[1] = values[iB];

				return true;
			}
		}
	}

	return false;

}

bool optim(int nb_values, int* values, int sum_value, int* output_couple){
	// assumes the list is sorted

	for(int ilow = 0; ilow != nb_values - 2; ++ilow){
		for(int ihigh = nb_values - 1; ihigh > ilow; --ihigh){

			int current_sum = values[ilow] + values[ihigh];

			if(current_sum == sum_value){
				output_couple[0] = values[ilow];
				output_couple[1] = values[ihigh];

				return true;
			}else if(current_sum < sum_value){
				break;
			}
		}
	}

	return false;

}

bool optim_reddit(int nb_values, int* values, int sum_value, int* output_couple){

	int ilow = 0;
	int ihigh = nb_values - 1;

	while(ilow < ihigh){
		int sum = values[ilow] + values[ihigh];

		if(sum > sum_value){
			--ihigh;
		}else if(sum < sum_value){
			++ilow;
		}else{
			output_couple[0] = values[ilow];
			output_couple[1] = values[ihigh];

			return true;
		}
	}

	return false;
}

int main(){
	// Problem data
	int nb_values = 7;
	int array[nb_values] = {1, 3, 5, 8, 12, 13, 22};
	int sum_value = 19;
	int max_couple = 3;
	int output_couple[max_couple * 2] = {-1, -1};

	printf("naive_nsquare solution: %i ", naive_nsquare(nb_values, array, sum_value, output_couple));
	printf(" with %i %i\n", output_couple[0], output_couple[1]);
	printf("optim solution: %i ", optim(nb_values, array, sum_value, output_couple));
	printf(" with %i %i\n", output_couple[0], output_couple[1]);
	printf("optim_reddit solution: %i ", optim_reddit(nb_values, array, sum_value, output_couple));
	printf(" with %i %i\n", output_couple[0], output_couple[1]);

	// Performance testing
	unsigned int nexecutions = 10000000;

	clock_t begin_naive = clock();
	for(unsigned int inaive = 0; inaive != nexecutions; ++inaive){
		naive_nsquare(nb_values, array, sum_value, output_couple);
	}
	clock_t end_naive = clock();

	clock_t begin_optim = clock();
	for(unsigned int ioptim = 0; ioptim != nexecutions; ++ioptim){
		optim(nb_values, array, sum_value, output_couple);
	}
	clock_t end_optim = clock();

	clock_t begin_optim_reddit = clock();
	for(unsigned int ioptim = 0; ioptim != nexecutions; ++ioptim){
		optim_reddit(nb_values, array, sum_value, output_couple);
	}
	clock_t end_optim_reddit = clock();

	printf("naive_nsquare: %f\n", (double)(end_naive - begin_naive) / CLOCKS_PER_SEC);
	printf("optim: %f\n", (double)(end_optim - begin_optim) / CLOCKS_PER_SEC);
	printf("optim_reddit: %f\n", (double)(end_optim_reddit - begin_optim_reddit) / CLOCKS_PER_SEC);
	printf("ratio_optim_naive: %f\n", (double)(end_optim - begin_optim) / (double)(end_naive - begin_naive));
	printf("ratio_optim_reddit_naive: %f\n", (double)(end_optim_reddit - begin_optim_reddit) / (double)(end_naive - begin_naive));
	printf("ratio_optim_reddit_optim: %f\n", (double)(end_optim_reddit - begin_optim_reddit) / (double)(end_optim - begin_optim));
}
