#include <stdio.h>
#include <mpi.h>

// Using OpenMPI 1.10.7 on ECS Servers
int main( int argc, char *argv[] )
{
	int rank, size;
	double b_starttime, b_endtime;
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	
	float a = 479;

	// === blocking transmission ===
	b_starttime = MPI_Wtime();
	if (rank == 0) {
		printf("\n=== BEGIN BLOCKING TRANSMISSION ===\n");
		MPI_Send(&a, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD);
		printf("P_0 sent %f to P_1\n", a);
	} else if (rank == 1) {
		MPI_Recv(&a, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		b_endtime = MPI_Wtime();
		printf("P_1 received %f from P_0\n", a);
		printf("Total Time: %f (seconds)\n", b_endtime-b_starttime);
	}
	
	MPI_Finalize();
	return 0;
}