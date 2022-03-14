// gcc -std=c99 parallel-loop-2.c -fopenmp
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#define N 32

int main(int argc, char **argv)
{
    int array[N];
    int i, tid;
    int sum = 0;

    #pragma omp parallel private(i, tid) shared(array, sum) num_threads(8)
    {
        tid = omp_get_thread_num();

        #pragma omp for
        for (i = 0; i < N; i++)
        {
            array[i] = i;
            printf("thread %d assigning %d to array[%d]\n",tid, array[i], i);
            
            #pragma omp critical
            sum += (array[i]%2 == 0 ? 1 : 0 );
        }
    }
    printf("there are %d even numbers\n", sum);
    return 0;
}
