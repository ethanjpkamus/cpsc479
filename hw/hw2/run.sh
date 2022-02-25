clear

rm *.out

echo "=== BEGIN SINGLE BLOCKING TRANSMISSION ==="
mpicc one-transmission.c -o one-transmission.out
mpirun -n 2 ./one-transmission.out

echo "=== BEGIN SINGLE NON-BLOCKING TRANSMISSION ==="
mpicc one-transmission-nonblocking.c -o one-transmission-nonblocking.out
mpirun -n 2 ./one-transmission-nonblocking.out

echo "=== BEGIN ROUND TRIP BLOCKING COMMUNICATION ==="
mpicc two-transmission.c -o two-transmission.out
mpirun -n 2 ./two-transmission.out

echo "=== BEGIN ROUND TRIP NON-BLOCKING COMMUNICATION ==="
mpicc two-transmission-nonblocking.c -o two-transmission-nonblocking.out
mpirun -n 2 ./two-transmission-nonblocking.out

echo "===== RING EXAMPLE ====="
mpicc timed-ring.c -o timed-ring.out

echo "=== 4 processes ==="
mpirun -n 4 ./timed-ring.out
echo

echo "=== 8 processes ==="
mpirun -n 8 ./timed-ring.out
echo

echo "=== 10 processes ==="
mpirun -n 10 ./timed-ring.out
echo

echo "=== 12 processes ==="
mpirun -n 12 ./timed-ring.out
echo