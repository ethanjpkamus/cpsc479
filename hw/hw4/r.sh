clear
rm *.out

echo '=== exercise 1 ==='
gcc -std=c99 ex1.c -o ex1.out -fopenmp
./ex1.out

echo
echo '=== exercise 2 ==='
gcc -std=c99 ex2.c -o ex2.out -fopenmp
./ex2.out

# echo '=== exercise 3 ==='
# gcc -std=c99 ex3.c -o ex3.out -fopenmp
# ./ex3.out