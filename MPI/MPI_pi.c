#include <stdlib.h> // rand / srand / atoi
#include <stdio.h> // printf
#include <stdbool.h> // bool
#include <mpi.h> // MPI_

float frand(){
	return ((float)rand()) / RAND_MAX;
}

// checks if the point of coordinates (x, y) is inside the circle of radius 1 centered at (0, 0)
bool is_inside_circle(float x, float y){
	if(x * x + y * y < 1.f){
		return true;
	}

	return false;
}

int main(int argc, char* argv[]){
	int MPI_ERROR;
	int MPI_CPU_COUNT;
	int MPI_CPU_RANK;
	int MPI_ROOT_CPU_RANK = 0;

	MPI_ERROR = MPI_Init(&argc, &argv);
	MPI_ERROR = MPI_Comm_size(MPI_COMM_WORLD, &MPI_CPU_COUNT);
	MPI_ERROR = MPI_Comm_rank(MPI_COMM_WORLD, &MPI_CPU_RANK);

	{
		// splitting the task among CPUs
		int total_samples = 1000;
		if(argc > 1){ // a command line argument is provided
			total_samples = atoi(argv[1]);
		}

		int cpu_samples = total_samples / MPI_CPU_COUNT;

		if(MPI_CPU_RANK == (MPI_CPU_COUNT - 1)){
			int missing_samples = total_samples - MPI_CPU_COUNT * cpu_samples;

			cpu_samples += missing_samples;
		}

		// each CPU does its task
		srand(MPI_CPU_RANK); // seed each CPU to a different initial value to avoid sampling the same points
		int cpu_valid_samples = 0;
		for(int isample = 0; isample != cpu_samples; ++isample){
			float x = frand();
			float y = frand();

			bool sample_is_inside = is_inside_circle(x, y);
			cpu_valid_samples += (int)sample_is_inside;
		}
		float cpu_valid_probability = (float)cpu_valid_samples / (float)total_samples;

		// reducing results
		float global_valid_probability = 0;
		MPI_Reduce(&cpu_valid_probability, &global_valid_probability, 1, MPI_FLOAT, MPI_SUM, MPI_ROOT_CPU_RANK, MPI_COMM_WORLD);

		// printing results on the root
		if(MPI_CPU_RANK == MPI_ROOT_CPU_RANK){
			float value_of_pi = 4 * global_valid_probability;
			printf("approximation of pi %f\n", value_of_pi);
		}
	}


	MPI_ERROR = MPI_Finalize();

	return 0;
}
