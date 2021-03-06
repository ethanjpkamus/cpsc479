#include <stdio.h>
#include <mpi.h>
 
int main( int argc, char *argv[] )
{
	//implementation of ring example with timer
	int rank, size, token;

	double starttime, endtime;
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	// printf( "I am %d of %d\n", rank, size );
	
	//the token should not change, stays -1
	starttime = MPI_Wtime();
	if (rank != 0) {
		MPI_Recv(&token, 1, MPI_INT, (rank - 1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("P_%d received token %d from P_%d\n", rank, token, (rank - 1) % size);
	} else {
		// Set the token's value if you are process 0
		token = 7;
 	}

	MPI_Send(&token, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);

	// Now process 0 can receive from the last process.
	if (rank == 0) {
		MPI_Recv(&token, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("P_%d received token %d from P_%d\n", rank, token, size - 1);
		endtime = MPI_Wtime();
		printf("The total time is: %f (seconds)\n", endtime-starttime);
	}
	
	MPI_Finalize();
}
