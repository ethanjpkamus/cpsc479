#include <stdio.h>
#include <mpi.h>

// passing array of ints between processes
int main( int argc, char *argv[] )
{
	
	int rank, size;
	MPI_Float starttime, endtime;
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	printf("I am process %d\n", rank);
	
	int a, b = 0;
	printf("Process %d has values a: %d and b: %d\n", rank, a, b);
	if (rank == 0) {
		a = 1;
		b = 2;
		MPI_Send(&a, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Send(&b, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		starttime = MPI_Wtime();
		printf("Process 0 sent a: %d and b: %d to process 1\n", a, b);
	} else if (rank == 1) {
		MPI_Recv(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&b, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		endtime = MPI_Wtime();
		printf("Process 1 received a: %d and b: %d from process 0\n", a, b);
		printf("The total time is %d\n", endtime - starttime);
	}
	printf("Process %d has values a: %d and b: %d\n", rank, a, b);
	MPI_Finalize();
	return 0;
}
