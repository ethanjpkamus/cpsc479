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
	printf("I am process %d\n", rank);
	
	int a = 3;
	printf("P_%d has values a: %d\n", rank, a);
	if (rank == 0) {
		starttime = MPI_Wtime();
		
		//send to 1
		MPI_Isend(&a, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		printf("P_0 sent a: %d to P_1\n", a);
		
		//receive from 1
		MPI_Irecv(&a, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		//wait here!
		printf("P_0 received a: %d from P_1\n", a);
		endtime = MPI_Wtime();
		printf("The total time is %d\n", endtime - starttime);
	} else if (rank == 1) {
		//receive from 0
		MPI_Irecv(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		//wait here!
		printf("P_1 received a: %d P_0\n", a);
		
		//send to 0
		MPI_Isend(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		printf("P_1 sent a: %d to P_0\n", a);
	}
	printf("Process %d has values a: %d\n", rank, a);
	MPI_Finalize();
	return 0;
}
