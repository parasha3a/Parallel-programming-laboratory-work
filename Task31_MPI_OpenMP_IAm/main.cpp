#include <mpi.h>
#include <omp.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank_mpi, size_mpi;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank_mpi);
    MPI_Comm_size(MPI_COMM_WORLD, &size_mpi);

    int n = 0;  // количество нитей

    // Процесс 0 вводит количество нитей
    if (rank_mpi == 0) {
        printf("Enter number of threads: ");
        scanf_s("%d", &n);
    }

    // Рассылка количества нитей всем процессам
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Устанавливаем количество нитей
    omp_set_num_threads(n);

    #pragma omp parallel
    {
        int rank_omp = omp_get_thread_num();
        int size_omp = omp_get_num_threads();
        
        printf("I am %d thread from %d process. Number of hybrid threads = %d\n",
               rank_omp, rank_mpi, size_omp * size_mpi);
    }

    MPI_Finalize();
    return 0;
}

