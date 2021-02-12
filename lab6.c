//#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

int vecsize = 400000000;
int main(int argc, char *argv[])
{
    printf("what");
    exit(-1);


    int * vec1 = malloc(vecsize * sizeof(int *));
    for (int i=0; i < vecsize; i++)
        vec1[i] = i + 1;
    int odd_num_seq= 0, odd_num_par = 0;
    int i =0;
    //omp_set_num_threads(atoi(argv[1]));

    //double start = omp_get_wtime();
  //  #pragma omp parallel for
    for(i=0; i<vecsize; i++)
    if(vec1[i] % 2 != 0){
    //    #pragma omp critical 
        odd_num_par += 1;
    }
    //double end = omp_get_wtime();

    printf("Vec size: %d\n", vecsize);
    //printf("[PAR]:: start = %.16g\nend = %.16g\ndiff = %.16g\n", start, end, end-start);
    //double diff1 = end-start;

    //start = omp_get_wtime();
    for(int i=0; i<vecsize; i++)
        if(vec1[i] % 2 != 0){odd_num_seq += 1;}
    //end = omp_get_wtime();
    printf("\n\n");
    //printf("[SEQ]:: start = %.16g\nend = %.16g\ndiff = %.16g\n", start, end, end-start);
    //double diff2 = end - start;
    //printf("Diff: %f\n", diff2/diff1);
}