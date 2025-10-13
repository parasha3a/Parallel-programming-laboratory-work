#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank_mpi, size_mpi;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank_mpi);
    MPI_Comm_size(MPI_COMM_WORLD, &size_mpi);

    long long N = 0;

    // Процесс 0 вводит параметр N
    if (rank_mpi == 0) {
        printf("Enter N (precision): ");
        scanf_s("%lld", &N);
    }

    // Рассылка параметра N
    MPI_Bcast(&N, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    double h = 1.0 / (double)N;
    double local_sum = 0.0;

    // Каждый процесс обрабатывает свою часть итераций
    #pragma omp parallel for reduction(+:local_sum)
    for (long long i = rank_mpi; i < N; i += size_mpi) {
        double x = h * ((double)i + 0.5);
        local_sum += 4.0 / (1.0 + x * x);
    }

    local_sum *= h;

    // Сбор результатов на процессе 0
    double pi = 0.0;
    MPI_Reduce(&local_sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank_mpi == 0) {
        printf("Calculated PI = %.8f\n", pi);
    }

    MPI_Finalize();
    return 0;
}

