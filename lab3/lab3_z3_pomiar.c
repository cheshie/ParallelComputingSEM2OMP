#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int size = 4;
	int M[4][4] = {
		{1,2,3,4},
		{1,2,3,4},
		{1,2,3,4},
		{1,2,3,4}
	};
	
	int sum_seq = 0;
	int sum_par = 0;
	
	// Seq sum
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			sum_seq+= M[i][j];

	// Par sum
	int threads = 8;
	omp_set_num_threads(threads);
	double start = omp_get_wtime();
	#pragma omp parallel for shared(size, M) reduction(+:sum_par)
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			sum_par += M[i][j];
	
	double end = omp_get_wtime();
	printf("Liczba watkow = %d\n", threads);
	printf("start = %.16g\nend = %.16g\ndiff = %.16g\n", start, end, end-start);
	
	//printf("Suma elementow macierzy: (seq): %d (par): %d\n", sum_seq, sum_par);

	return 0;
}
