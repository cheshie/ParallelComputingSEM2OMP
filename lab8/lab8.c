#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    // create matrice
    int nmax = 1400;
    int n = nmax - 2;
    int a[nmax][nmax];
    
    // fill with some numbers
    for (int i=0; i<nmax; i++)
        for (int j=0; j<nmax; j++)
            a[i][j] = i;

    //omp_set_num_threads(atoi(argv[1]));
    // Computation
    double start = omp_get_wtime();
    //#pragma omp for ordered(2) collapse(2)
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            //#pragma omp ordered depend(sink: i-1, j) depend(sink: i, j-1)
            a[i][j] = a[i][j+2] + a[i+1][j-1];
            //#pragma omp ordered depend(source)
        }
    }
    double end = omp_get_wtime();
    printf("size: %d\n", nmax);
    printf("[PAR]:: start = %.16g\nend = %.16g\ndiff = %.16g\n", start, end, end-start);
}