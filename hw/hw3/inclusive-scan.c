#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

// Using OpenMPI 1.10.7 on ECS Servers
int main( int argc, char *argv[] )
{
	int rank, size;
	int n = 1;
	srand(time(NULL));
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &size );

    // hard coded send buffer
    // int send[] = {3,1,7,1,4,1,6,3};

    int send = rand() % 100; // generate random number between 0-99
    int r;

    // scan will implicitly know all the previous calculations of r
    // so dont need recv buffer as an array
    // int recv[] = {0,0,0,0,0,0,0,0};

	// solution for hard coded version
    // MPI_Scan(&send[rank], &r, n, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    // printf("i am process %d and recieve range: %d - %d\n", rank, (r-send[rank])+1, r);
    
	// random version
	MPI_Scan(&send, &r, n, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    printf("i am process %d and recieve range: %d - %d\n", rank, (r-send)+1, r);
	MPI_Finalize();
	return 0;
}