#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    long N = 100000;
    long local_N;
    long local_count = 0, global_count = 0;
    double x, y;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc > 1) {
        N = atol(argv[1]);
    } else {
        N = 10000;
    }
    if (rank == 0) {
        printf("%ld\t", N);
    }

    srand(time(NULL) + rank); // Seed the random number generator

    local_N = N / size;
    for (long i = 0; i < local_N; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if (x*x + y*y <= 1.0) {
            local_count++;
        } }

 MPI_Reduce(&local_count, &global_count, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank == 0) {
        double pi_estimate = 4.0 * global_count / N;
        printf("%f\t", pi_estimate);
        printf("%f\t\n", fabs(pi_estimate - M_PI));
    }
    MPI_Finalize();
    return 0; }
