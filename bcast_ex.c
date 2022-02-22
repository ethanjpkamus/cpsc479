#include <stdio.h>

#include <mpi.h>

int main(int argc, char *argv[]) {
	int n = 5 ;
	int a[5];
	int i;
	int rank;
	int size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	for (i=0; i< 5; i++) a[i] = 0;
	printf("Process of rank %d has array [%d, %d, %d, %d %d] \n", rank, a[0],a[1],a[2],a[3],a[4]);
	if ( rank == 0 )
		for ( i = 0; i < n; i++ ) a[i] = i;
	MPI_Bcast(&a, n, MPI_INT, 0, MPI_COMM_WORLD);
	printf("Process of rank %d has array [%d, %d, %d, %d %d] \n", rank, a[0],a[1],a[2],a[3],a[4]);
	MPI_Finalize();

	return 0;
}
