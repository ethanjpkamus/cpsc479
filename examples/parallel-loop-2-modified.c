#include <stdio.h>

int main() {
    const int N=15;
    int i, a[N], tid;
    //initialize
    for (i=0; i < N; i++)
        a[i] = i;
    //compute sum
    int local_sum, sum=0;
    #pragma omp parallel private(i, local_sum, tid) shared(sum)
    {
        local_sum =0;
        tid = omp_get_thread_num();
        //the array is distributed statically between threads
        #pragma omp for schedule(static,1)
        for (i=0; i< N; i++) {
            local_sum += a[i];
            printf("Hello world from thread=%d with loop counter i=%d\n", tid, i);
        }
        //each thread calculated its local_sum. ALl threads have to add to
        //the global sum. It is critical that this operation is atomic.
        #pragma omp critical
        sum += local_sum;
    }
    printf("sum=%d should be %d\n", sum, N*(N-1)/2);
}