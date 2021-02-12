#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

int vecsize = 1000000;

int vecsum_odd(int *vec_a, int vecsize)
{
	int i;
	int sum = 0;
	#pragma omp parallel for reduction(+ : sum) 
	for(i=0; i<vecsize; i++)
		if((i+1) % 2 != 0){
		  sum += vec_a[i];
		}

	return sum;
}

int main(int argc, char *argv[])
{
	double startapp = omp_get_wtime();

	int * vec1 = malloc(vecsize * sizeof(int *));
	for (int i=0; i < vecsize; i++)
		vec1[i] = i + 1;

	int sum_par = 0;
	omp_set_num_threads(atoi(argv[1]));
	int thid;
	double startpar = omp_get_wtime();
	#pragma omp parallel sections
	{ 
		thid = omp_get_num_threads();
		#pragma omp section
		vecsum_odd(vec1, vecsize/2);
        #pragma omp section
		sum_par = vecsum_odd(vec1+vecsize/2, vecsize);
	}
	double endpar = omp_get_wtime();
    printf("[PARALLEL]:: start = %.16g\nend = %.16g\ndiff = %.16g\n",
	 	startpar, endpar, endpar-startpar);
    double timepar = endpar - startpar;

	double endapp = omp_get_wtime();
    printf("[APP TIME]:: start = %.16g\nend = %.16g\ndiff = %.16g\n", startapp, 
		endapp, endapp-startapp);
    double timeapp = endapp - startapp;

	printf("Elements: %d\n", vecsize);
	printf("Threads: %d\n", thid);
	printf("Calulated time: %f\n", timeapp / timepar);
}
