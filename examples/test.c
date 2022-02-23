#include <stdio.h>
#include <mpi.h>

// passing array of ints between processes
int main( int argc, char *argv[] )
{
	
	int rank, size;
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	printf( "I am %d of %d\n", rank, size );
	
	int a, b = 0;
	printf("Process %d has values a: %d and b: %d\n", rank, a, b);
	if (rank == 0) {
		a = 1;
		b = 2;
		MPI_Send(&a, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Send(&b, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		printf("Process 0 sent array [%d,%d,%d] to process 1\n", A[0], A[1], A[2]);
	} else if (rank == 1) {
		MPI_Recv(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&b, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process 1 received array[%d,%d,%d] from process 0\n", A[0],A[1],A[2]);
	}
	printf("Process %d has values a: %d and b: %d\n", rank, a, b);
	MPI_Finalize();
	return 0;
}
