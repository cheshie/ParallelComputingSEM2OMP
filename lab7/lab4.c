#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

int mSize = 1000;

int main(int argc, char *argv[])
{
	double startapp = omp_get_wtime();

	int **A = (int **)malloc(mSize * sizeof(int *));	
	int **B = (int **)malloc(mSize * sizeof(int *));
	int **C = (int **)malloc(mSize * sizeof(int *));
	int **C1= (int **)malloc(mSize * sizeof(int *));

	for (int i=0; i < mSize; i++){
		A[i] = (int *)malloc(mSize * sizeof(int));
		B[i] = (int *)malloc(mSize * sizeof(int));
		C[i] = (int *)malloc(mSize * sizeof(int));
		C1[i] = (int *)malloc(mSize * sizeof(int));
	}

	int thid = 0;

	// fill matrices
	for(int i=0; i<mSize; ++i)
		for (int j=0; j<mSize; ++j){
		A[i][j] = i * j + 5;
		B[i][j] = i + j + 5;
		C[i][j] = 0;
		C1[i][j] = 0;
	}

	omp_set_num_threads(atoi(argv[1]));
	double startpar = omp_get_wtime();
	#pragma omp parallel
	{
		thid = omp_get_num_threads();
		#pragma omp parallel for shared(C1) firstprivate(A, B) schedule(guided)
		for (int i=0; i<mSize; ++i)
			for(int j=0; j<mSize; ++j)
				for (int k=0; k<mSize; ++k)
					C1[i][j] += A[i][k] * B[k][j];
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
}
