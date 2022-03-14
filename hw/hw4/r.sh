clear
rm *.out

gcc -std=c99 ex1.c -o ex1.out -fopenmp
./ex1.out

# mpicc -std=c99 ex2.c -o ex2.out
# mpirun -n 8 ./ex2.out

# mpicc -std=c99 ex3.c -o ex3.out
# mpirun -n 8 ./ex3.out