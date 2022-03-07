// gcc -std=c99 parallel-loop-2.c -fopenmp
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int a[100];
    #pragma omp parallel for
    for (int i = 0; i < 100; i++) {
        a[i] = 2 * i;
        printf("assigning i=%d\n", i);
    }
    return 0;
}