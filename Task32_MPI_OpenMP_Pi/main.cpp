#include <mpi.h>
#include <omp.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank_mpi, size_mpi;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank_mpi);
    MPI_Comm_size(MPI_COMM_WORLD, &size_mpi);

    long long N = 0;

    // Процесс 0 вводит параметр N
    if (rank_mpi == 0) {
        printf("Enter N (precision): ");
        fflush(stdout);
        scanf_s("%lld", &N);
    }

    // Рассылка параметра N
    MPI_Bcast(&N, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    // Составное правило Симпсона: N — число подотрезков на [0,1], N чётное и >= 2
    if (N < 2) {
        N = 2;
    }
    if (N % 2 != 0) {
        N++;
    }

    const double h = 1.0 / (double)N;
    double local_sum = 0.0;

    // Узлы x_j = j*h, j = 0..N; веса 1,4,2,4,...,2,4,1 → π ≈ (h/3) * Σ w_j * f(x_j)
    #pragma omp parallel for reduction(+:local_sum)
    for (long long j = rank_mpi; j <= N; j += size_mpi) {
        const double x = h * (double)j;
        const double f = 4.0 / (1.0 + x * x);
        double w;
        if (j == 0 || j == N) {
            w = 1.0;
        } else if (j % 2 == 1) {
            w = 4.0;
        } else {
            w = 2.0;
        }
        local_sum += w * f;
    }

    double total = 0.0;
    MPI_Reduce(&local_sum, &total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank_mpi == 0) {
        const double pi = (h / 3.0) * total;
        printf("Calculated PI = %.8f (Simpson, N=%lld subintervals)\n", pi, N);
    }

    MPI_Finalize();
    return 0;
}

