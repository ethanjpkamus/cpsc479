clear

rm *.out

mpicc one-transmission.c -o one-transmission.out
mpirun -n 2 ./one-transmission.out

mpicc one-transmission-nonblocking.c -o one-transmission-nonblocking.out
mpirun -n 2 ./one-transmission-nonblocking.out
