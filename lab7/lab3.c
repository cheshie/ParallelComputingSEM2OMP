#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int mSize = 10000;

int main(int argc, char ** argv)
{
	double startapp = omp_get_wtime();

	int **M = (int **)malloc(mSize * sizeof(int *));
	for (int i=0; i < mSize; i++)
		M[i] = (int *)malloc(mSize * sizeof(int));

	for (int i =0; i<mSize; i++)
	  for(int j=0; j<mSize; j++)
	     M[i][j] = i + 1;
	
	int sum_seq = 0;
	int sum_par = 0;
	int thid    = 0;

	omp_set_num_threads(atoi(argv[1]));

	// Par sum
	double startpar = omp_get_wtime();
	#pragma omp parallel
	{
		thid = omp_get_num_threads();
		#pragma omp parallel for shared(M) reduction(+:sum_par)
		for(int i=0; i<mSize; i++)
			for(int j=0; j<mSize; j++)
				sum_par += M[i][j];
	}	
	double endpar = omp_get_wtime();
    printf("[PARALLEL]:: start = %.16g\nend = %.16g\ndiff = %.16g\n",
	 	startpar, endpar, endpar-startpar);
    double timepar = endpar - startpar;


	double endapp = omp_get_wtime();
    printf("[APP TIME]:: start = %.16g\nend = %.16g\ndiff = %.16g\n", startapp, 
		endapp, endapp-startapp);
    double timeapp = endapp - startapp;


	printf("Elements: %d\n", mSize);
	printf("Threads: %d\n", thid);
	printf("Calulated time: %f\n", timeapp / timepar);

	return 0;
}
