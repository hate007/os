#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char *argv[]) {
    int rank, size;
    int numbers[ARRAY_SIZE];
    int local_max=0;
    int global_max=0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srand(rank);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        numbers[i] = rand() % 1001;
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (numbers[i] > local_max) {
            local_max = numbers[i];
        }
    }

    MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("The maximum number is: %d\n", global_max);
    }

    MPI_Finalize();
    
    return 0;
}
