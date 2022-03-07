clear
rm *.out

mpicc -std=c99 inclusive-scan.c -o inclusive-scan.out
mpirun -n 8 ./inclusive-scan.out