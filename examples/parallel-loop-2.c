//use a binary semaphore to make sure sum is computed properly
// gcc -std=c99 parallel-loop-2.c -fopenmp
#include <stdio.h>

int main() {
    const int N=100;
    int a[N];
    
    //initialize
    for (int i=0; i < N; i++)
        a[i] = i;
    
    //compute sum
    int local_sum, sum=0;
    #pragma omp parallel private(local_sum) shared(sum)
    {
        local_sum = 0;
        //the array is distributde statically between threads
        #pragma omp for schedule(static,1) // specify the type of schedule. static,1 indicates that each thread gets one iteration
        for (int i=0; i < N; i++) {
            local_sum += a[i];
        }

        //each thread calculated its local_sum. ALl threads have to add to
        //the global sum. It is critical that this operation is atomic.
        #pragma omp critical
        sum += local_sum;
    }
    printf("sum=%d should be %d\n", sum, N*(N-1)/2);
}