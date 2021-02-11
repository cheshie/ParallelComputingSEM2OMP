#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    #pragma omp parallel sections num_threads(4)
    {
			  #pragma omp section
        printf("Hello from thread %d\n", omp_get_thread_num());
        #pragma omp section
        printf("Hello from thread %d\n", omp_get_thread_num());
    }
}
