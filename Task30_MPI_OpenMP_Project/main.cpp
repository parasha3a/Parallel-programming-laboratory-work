#include <mpi.h>
#include <omp.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank_mpi, size_mpi;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank_mpi);
    MPI_Comm_size(MPI_COMM_WORLD, &size_mpi);

    // Операторы MPI_Init и MPI_Finalize
    // Между ними создаем параллельную область с помощью OpenMP

    #pragma omp parallel
    {
        int rank_omp = omp_get_thread_num();
        int size_omp = omp_get_num_threads();
        
        printf("Process %d, Thread %d: Hello from hybrid MPI+OpenMP!\n", 
               rank_mpi, rank_omp);
    }

    MPI_Finalize();
    return 0;
}

