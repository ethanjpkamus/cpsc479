#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
	int n = 5;
	int a[5];
	int b[] = {0,0};
	int i;
	int rank;
	int size;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	b[0]=b[1]=rank+1;
	for (i=0; i< n; i++) a[i] = 0;
	
	printf("Process of rank %d has array b=[%d,%d] a=[%d, %d, %d, %d, %d]\n", rank, b[0], b[1], a[0], a[1], a[2], a[3], a[4]);
	MPI_Reduce(&b, &a, 2, MPI_INT, MPI_PROD, 4, MPI_COMM_WORLD);
	printf("After reduce, Process of rank %d has array a=[%d, %d, %d, %d, %d]\n", rank, a[0], a[1], a[2], a[3], a[4]);
	
	MPI_Finalize();	
	return 0;
}
