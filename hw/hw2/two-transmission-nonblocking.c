#include <stdio.h>
#include <mpi.h>

// passing array of ints between processes
int main( int argc, char *argv[] )
{
	
	int rank, size;
	double starttime, endtime;
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	// printf("I am process %d\n", rank);
	
	float a = 479;
	
	MPI_Request ireq;
	MPI_Status istatus;

	//=== non-blocking ===
	starttime = MPI_Wtime();
	if (rank == 0) {
		printf("\n=== BEGIN NON-BLOCKING TRANSMISSIONS (2 TRANSMISSIONS) ===\n");

		//send to 1
		MPI_Isend(&a, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD, &ireq);
		printf("P_0 sent a: %f to P_1\n", a);
		
		//receive from 1
		MPI_Irecv(&a, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD, &ireq);
		MPI_Wait(&ireq, &istatus);
		printf("P_0 received a: %f from P_1\n", a);

		endtime = MPI_Wtime();
		printf("The total time is %f\n", endtime - starttime);
	} else if (rank == 1) {
		//receive from 0
		MPI_Irecv(&a, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &ireq);
		MPI_Wait(&ireq, &istatus);
		printf("P_1 received a: %f P_0\n", a);
		
		//send to 0
		MPI_Isend(&a, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &ireq);
		printf("P_1 sent a: %f to P_0\n", a);
	}
	//printf("Process %f has values a: %f\n", rank, a);
	MPI_Finalize();
	return 0;
}
