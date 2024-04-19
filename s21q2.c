#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char *argv[]) {
    int rank, size;
    int i, local_sum = 0, total_sum = 0;
    int array[ARRAY_SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srand(rank); 
    for (i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 1001; 
    }

    for (i = 0; i < ARRAY_SIZE; i++) {
        if (array[i] % 2 == 0) {
            local_sum += array[i];
        }
    }
    printf("Process : %d\n", rank+1);
     printf("My sum of even numbers: %d\n", local_sum);

    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        printf("Total sum of even numbers: %d\n", total_sum);
    }

    MPI_Finalize();

    return 0;
}
