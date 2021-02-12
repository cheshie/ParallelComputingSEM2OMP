#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

int vecsize = 10000000;
int main(int argc, char *argv[])
{
    double startapp = omp_get_wtime();

    int * vec1 = malloc(vecsize * sizeof(int *));
    for (int i=0; i < vecsize; i++)
        vec1[i] = i + 1;
    int odd_num_seq= 0, odd_num_par = 0;
    int i =0;
    omp_set_num_threads(atoi(argv[1]));

    double startpar = omp_get_wtime();
    int thid;
    #pragma omp parallel
    {
        thid = omp_get_num_threads();
        #pragma omp parallel for
        for(i=0; i<vecsize; i++)
        if(vec1[i] % 2 != 0){
        #pragma omp critical 
        odd_num_par += 1;
    }
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