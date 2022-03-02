//compute the sum of two arrays in parallel
#include <stdio.h>
#include <omp.h>
#define N 60

int main(void) {
    float a[N], b[N], c[N];
    int i;
    int tid;
    /* Initialize arrays a and b */
    for (i = 0; i < N; i++) {
        a[i] = i * 2.0;
        b[i] = i * 3.0;
    }
    /* Compute values of array c = a+b in parallel. */
    #pragma omp parallel shared(a, b, c) private(i,tid)
    {
        /* Obtain thread number */
        tid = omp_get_thread_num();
        //printf("Hello World from thread = %d\n", tid);
        #pragma omp for
        for (i = 0; i < N; i++) {
            c[i] = a[i] + b[i];
            printf("Hello World from thread = %d with loop counter i=%d\n", tid,i);
        }
    }
    for(i=0; i< N; i++) {
        printf ("%f ", c[i]);
    }
    printf("\n");
}