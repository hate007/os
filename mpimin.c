#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char *argv[]) {
    int rank, size;
    int numbers[ARRAY_SIZE];
    int local_min=9999;
    int global_min=0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srand(rank);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        numbers[i] = rand() % 1001;
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (numbers[i] < local_min) {
            local_min = numbers[i];
        }
    }

    MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("The minimum number is: %d\n", global_min);
    }

    MPI_Finalize();
    
    return 0;
}
