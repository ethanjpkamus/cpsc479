#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

// Using OpenMPI 1.10.7 on ECS Servers
int main( int argc, char *argv[] )
{
	int rank, size;
    int n = 8;
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	// int send[n];
    // int recv[n];
    int send[] = {3,1,7,1,4,1,6,3};
    int recv[] = {0,0,0,0,0,0,0,0};
	
    MPI_Scan(&send, &recv, n, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    
    // print recv for the sake of testing (dont include in the final program)
    printf("i am rank %d with [", rank);
    for(int i = 0; i < n-2; ++i) {
        printf("%d, ", recv[i]);
    }
    printf("%d]\n",recv[n-1]);

	MPI_Finalize();
	return 0;
}