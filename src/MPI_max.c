#include <stdio.h> // printf
#include <stdlib.h> // atoi
#include <mpi.h>
#include <math.h> // sin


float x_value(int sampleID, int N){
	return (float)sampleID / (float)N * 2 * M_PI;
}

float f_value(float x){
	return sin(x);
}


int main(int argc, char* argv[]){

	int MPI_ERROR;
	int MPI_CPU_COUNT;
	int MPI_CPU_RANK;
	int MPI_ROOT_CPU_RANK = 0;
	int MPI_TAG_OFFSET = 0;

	MPI_ERROR = MPI_Init(&argc, &argv);
	MPI_ERROR = MPI_Comm_size(MPI_COMM_WORLD, &MPI_CPU_COUNT);
	MPI_ERROR = MPI_Comm_rank(MPI_COMM_WORLD, &MPI_CPU_RANK);

	{
		// identifying & dispatching task
		int N = 999;
		if(argc > 1){
			N = atoi(argv[1]);
		}
		int total_samples = N + 1; // [0; N] ie N + 1 values to compare

		int cpu_samples = total_samples / MPI_CPU_COUNT;
		int cpu_samples_offset = MPI_CPU_RANK * cpu_samples;

		// the last CPU may do more than the others
		if(MPI_CPU_RANK == (MPI_CPU_COUNT - 1)){
			int missing_samples = total_samples - cpu_samples * MPI_CPU_COUNT;
			cpu_samples += missing_samples;
		}

		//printf("CPU %i samples %i\n", MPI_CPU_RANK, cpu_samples);

		// each CPU does its task
		int cpu_max_ID = 0;
		float cpu_max_VALUE = f_value(x_value(cpu_samples_offset, N)); // first value for this CPU
		printf("CPU %i sample ID %i sample_value %f\n", MPI_CPU_RANK, cpu_max_ID, cpu_max_VALUE);

		for(int isample = 1; isample < cpu_samples; ++isample){
			int sampleID = cpu_samples_offset + isample;
			float sample_value = f_value(x_value(sampleID, N));

			printf("CPU %i sample ID %i sample_value %f\n", MPI_CPU_RANK, sampleID, sample_value);

			if(sample_value > cpu_max_VALUE){
				cpu_max_ID = sampleID;
				cpu_max_VALUE = sample_value;
			}
		}


		// each CPU sends max_sample_ID, max_sample_VALUE, cpu_ID to the root CPU
		int msg_byte_size = sizeof(int) + sizeof(float);
		if(MPI_CPU_RANK != MPI_ROOT_CPU_RANK){
			char byte_data[msg_byte_size];

			int* byte_max_sample_ID = (int*)(&byte_data[0]);
			float* byte_max_sample_VALUE = (float*)(&byte_data[sizeof(int)]);

			*byte_max_sample_ID = cpu_max_ID;
			*byte_max_sample_VALUE = cpu_max_VALUE;

			MPI_Send(&byte_data, msg_byte_size, MPI_BYTE, MPI_ROOT_CPU_RANK, MPI_TAG_OFFSET + MPI_CPU_RANK, MPI_COMM_WORLD);

		// the root CPU reduces all data
		}else{

			int max_ID = cpu_max_ID;
			float max_VALUE = cpu_max_VALUE;
			int max_CPU_ID = MPI_ROOT_CPU_RANK;

			char byte_data[msg_byte_size];

			for(int iCPU = 1; iCPU != MPI_CPU_COUNT; ++iCPU){
				MPI_Recv(&byte_data, msg_byte_size, MPI_BYTE, iCPU, MPI_TAG_OFFSET + iCPU, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

				int* iCPU_max_sample_ID = (int*)(&byte_data[0]);
				float* iCPU_max_sample_VALUE = (float*)(&byte_data[sizeof(int)]);

				// reduce with the root CPU values
				if((*iCPU_max_sample_VALUE) > max_VALUE){
					max_ID = (*iCPU_max_sample_ID);
					max_VALUE = (*iCPU_max_sample_VALUE);
					max_CPU_ID = iCPU;
				}
			}

			// printing the result of the reduction
			printf("max sample %i max value %f sample cpu %i\n", max_ID, max_VALUE, max_CPU_ID);
		}
	}


	MPI_ERROR = MPI_Finalize();

	return 0;
}
