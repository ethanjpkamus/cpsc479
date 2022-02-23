#include <stdio.h>
#include <mpi.h>

// Using OpenMPI 1.10.7 on ECS Servers
int main( int argc, char *argv[] )
{
	int rank, size;
	float nb_starttime, nb_endtime;
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	
//	float precision = MPI_Wtick();
	float a = 479;

	MPI_Request ireq;
	MPI_Status istatus;

	// === non-blocking ===
	if (rank == 0) {
		printf("\n=== BEGIN NON-BLOCKING TRANSMISSION ===\n");
	        nb_starttime = MPI_Wtime() * MPI_Wtick();
	        MPI_Isend(&a, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD, &ireq);
	        printf("P_0 sent %f to P_1\n", a);
	} else if (rank == 1) {
	        MPI_Irecv(&a, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &ireq);
	        MPI_Wait(&ireq, &istatus);
	        nb_endtime = MPI_Wtime() * MPI_Wtick();
	        printf("P_1 recieved %f from P_0\n", a);

//        	nb_starttime *= precision;
//        	nb_endtime *= precision;
		printf("start: %f\nend: %f\n", nb_starttime, nb_endtime);
	        printf("Total time: %f (seconds)\n", nb_endtime-nb_starttime);
	}
	MPI_Finalize();
	return 0;
}
