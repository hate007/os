#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char *argv[]) {
    int rank, size;
    int numbers[ARRAY_SIZE];
    int local_sum = 0, total_sum = 0;
    double average;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srand(rank);

    for (int i = 0; i < ARRAY_SIZE; i++) {
        numbers[i] = rand() % 1001; 
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
        local_sum += numbers[i];
    }

    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        average = (double)total_sum / size;
        printf("Total sum: %d\n", total_sum);
        printf("Average: %.2f\n", average);
    }

    MPI_Finalize();

    return 0;
}
