#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

int vecsize = 899999990;

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
	int * vec1 = malloc(vecsize * sizeof(int *));
	for (int i=0; i < vecsize; i++)
		vec1[i] = i + 1;

	int sum_par = 0;
	double start = omp_get_wtime();
  //omp_set_num_threads(atoi(argv[1]));
	#pragma omp parallel sections
	{ 
		#pragma omp section
		vecsum_odd(vec1, vecsize/2);
    #pragma omp section
		sum_par = vecsum_odd(vec1+vecsize/2, vecsize);
	}
	double end = omp_get_wtime();
	//printf("Threads:  %d\n", atoi(argv[1]));
	printf("Vec size: %d\n", vecsize);
  printf("[PAR]:: start = %.16g\nend = %.16g\ndiff = %.16g\n", start, end, end-start);
  double diff1 = end-start;

	
	start = omp_get_wtime();
	int sum_seq = 0;
  for (int i=0; i<vecsize; i++)
		if ((i+1) %2 != 0)
			sum_seq += vec1[i];
	end = omp_get_wtime();
	printf("\n\n");
	printf("[SEQ]:: start = %.16g\nend = %.16g\ndiff = %.16g\n", start, end, end-start);
	double diff2 = end - start;
	printf("Diff: %f\n", diff2/diff1);
	//printf("Par sum: %d\n", sum_par);
	//printf("Seq sum: %d\n", sum_seq);
	
}
