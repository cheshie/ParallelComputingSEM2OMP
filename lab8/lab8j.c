#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char *argv[])
{

	int n = 100;
	int a[n][n], a2[n][n];

	for(int i=0; i<=n; i++)
	{
		for(int j=0; j<=n; j++)
		{
			a[i][j] = i+j;
 			a2[i][j] = i+j;

		}
	}

/* ---------------------------------------------------------------------------------------------------- */
	// program sekwencyjny

	double start = omp_get_wtime();

	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)
		{
			a[i][j] = a[i][j+2] + a[i+2][j-1]; 
		}
	}

	double end = omp_get_wtime();


	printf("Program sekwencyjny:\nstart = %.16g\nend = %.16g\ndiff = %.16g\n", start,end,end-start);

/* --------------------------------------------------------------------------------------------------- */
	int num = 8;
	// program rownolegly 
	omp_set_num_threads(num);
	start = omp_get_wtime();

	#pragma omp for ordered(2)
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)
		{
			#pragma omp ordered depend(sink:i,j+2), depend(sink:i+2,j-1)
			a2[i][j] = a2[i][j+2] + a2[i+2][j-1]; 
			#pragma omp ordered depend(source)
		}
	}

	end = omp_get_wtime();

	printf("Program rownolegly:\nstart = %.16g\nend = %.16g\ndiff = %.16g\n", start,end,end-start);

/* ----------------------------------------------------------------------------------------------------- */
	printf("-----------------------------------------------------------------------\n" );
	int ok = 0;
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)
		{
			if (a[i][j] =! a2[i][j])
			{
				ok = 1;
			}
		}
	}

	if (ok == 0)
	{
		printf("Wyniki są takie same\n");
	}
	else
	{
		printf("Wyniki się różnią\n");

		printf("a: \n");
		for(int i=0; i<=n; i++)
		{
			for(int j=0; j<=n; j++)
			{
				printf("%d ", a[i][j]);
			}
			printf("\n");
		}

		printf("a2: \n");
		for(int i=0; i<=n; i++)
		{
			for(int j=0; j<=n; j++)
			{
				printf("%d ", a2[i][j]);
			}
			printf("\n");
		}
	}

	return 0;
}


