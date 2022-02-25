#include <stdio.h>
#include <mpi.h>

// Using OpenMPI 1.10.7 on ECS Servers
int main( int argc, char *argv[] )
{
	int rank, size;
	double starttime, endtime;
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	
	float a = 479;

	// === blocking transmission ===
	starttime = MPI_Wtime();
	if (rank == 0) {
		MPI_Send(&a, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD);
		printf("P_0 sent %f to P_1\n", a);
	} else if (rank == 1) {
		MPI_Recv(&a, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		endtime = MPI_Wtime();
		printf("P_1 received %f from P_0\n", a);
		printf("Total Time: %f (seconds)\n\n", endtime-starttime);
	}
	
	MPI_Finalize();
	return 0;
}