#include <stdio.h>
#include <mpi.h>

// passing array of ints between processes
int main( int argc, char *argv[] )
{
	
	int rank, size;
	float starttime, endtime;
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	
	float a = 3;
//	float precision = MPI_Wtick();
//	printf("precision: %.10f\n", precision);
//	starttime = MPI_Wtime();
	if (rank == 0) {
		printf("\n=== BEGIN BLOCKING TRANSMISSIONS (2 TRANSMISSIONS) ===\n");
		starttime = MPI_Wtime() * MPI_Wtick();
		
		//send to 1
		MPI_Send(&a, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD);
		printf("P_0 sent %f to P_1\n", a);
		
		//receive from 1
		MPI_Recv(&a, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("P_0 received %f from P_1\n", a);
		endtime = MPI_Wtime() * MPI_Wtick();

//		starttime *= precision;
//		endtime *= precision;
		printf("start: %f\nend: %f\n", starttime, endtime);
		printf("Total Time: %f\n", endtime-starttime);
	} else if (rank == 1) {
		//receive from 0
		MPI_Recv(&a, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("P_1 received %f P_0\n", a);
		
		//send to 0
		MPI_Send(&a, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
		printf("P_1 sent %f to P_0\n", a);
	}
//	if (rank == 0) {
//		endtime = MPI_Wtime();
//		starttime *= precision;
//		endtime *= precision;

//		printf("start: %f\nend: %f\n", starttime, endtime);
//		printf("Total Time: %f\n", endtime-starttime);
//	}
	MPI_Finalize();
	return 0;
}
