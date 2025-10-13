#include <mpi.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long long N = 0;

    // Процесс 0 вводит параметр N
    if (rank == 0) {
        printf("Enter N (precision): ");
        scanf_s("%lld", &N);
    }

    // Широковещательная рассылка N
    MPI_Bcast(&N, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    double h = 1.0 / (double)N;
    double local_sum = 0.0;

    // Каждый процесс вычисляет свою часть суммы
    for (long long i = rank; i < N; i += size) {
        double x = h * ((double)i + 0.5);
        local_sum += 4.0 / (1.0 + x * x);
    }

    local_sum *= h;

    // Собираем все частичные суммы на процессе 0
    double pi = 0.0;
    MPI_Reduce(&local_sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Calculated PI = %.8f\n", pi);
    }

    MPI_Finalize();
    return 0;
}

