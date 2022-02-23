#include <stdio.h>
#include <mpi.h>
 
int main( int argc, char *argv[] )
{
	//implementation of ring example with timer
	int rank, size, token;
	//double starttime, endtime, totaltime;
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	printf( "I am %d of %d\n", rank, size );
	
	//the token should not change, stays -1
	if (rank != 0) {
		MPI_Recv(&token, 1, MPI_INT, (rank - 1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process %d received token %d from process %d\n", rank, token, (rank - 1) % size);
	} else {
		// Set the token's value if you are process 0
		token = 7;
		//starttime = MPI_Wtime();
		//printf("START TIME: %d \n", starttime);
 	}

	MPI_Send(&token, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);

	// Now process 0 can receive from the last process.
	if (rank == 0) {
		MPI_Recv(&token, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		//endtime = MPI_Wtime();
		//totaltime = endtime - starttime;
		printf("Process %d received token %d from process %d\n", rank, token, size - 1);
		//printf("END TIME: %d \n", MPI_Wtime());
		//printf("The total time is: %d \n", totaltime);
	}
	
	MPI_Finalize();
}
