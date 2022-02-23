#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
	int n = 12;
	int a[12];
	int b[] = {0,0};
	int i;
	int rank;
	int size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	b[0]=b[1]=rank;
	
	for (i=0; i< n; i++) a[i] = 0;
	printf("Process of rank %d has array b=[%d,%d]a=[", rank, b[0], b[1]);
	for(i=0; i < n-1; ++i) 
	{ printf("%d,", a[i]); }
	printf("%d]\n", a[i]);
	
	MPI_Allgather(&b, 2, MPI_INT, &a, 2, MPI_INT, MPI_COMM_WORLD);

	printf("Process of rank %d has array b=[%d,%d]a=[", rank, b[0], b[1]);
	for(i=0; i < n-1; ++i) 
	{ printf("%d,", a[i]); }
	printf("%d]\n", a[11]);
	
	MPI_Finalize();	
	return 0;
}
