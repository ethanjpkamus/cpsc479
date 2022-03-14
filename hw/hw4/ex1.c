// gcc -std=c99 parallel-loop-2.c -fopenmp
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#define N 32

int main(int argc, char **argv)
{
    int array[N];
    int i, tid;

    #pragma omp parallel private(i, tid) shared(array)
    {
        tid = omp_get_thread_num();

        #pragma omp for
        for (i = 0; i < N; i++)
        {
            array[i] = 0;
            printf("thread %d assigning %d to array[%d]\n",tid, array[i], i);
        }
    }
    return 0;
}