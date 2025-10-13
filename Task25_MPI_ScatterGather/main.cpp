#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = 0;
    
    // Процесс 0 вводит размер матриц
    if (rank == 0) {
        printf("Enter matrix size n (1 <= n <= 10, n^2 divisible by number of processes): ");
        scanf_s("%d", &n);
    }
    
    // Широковещательная рассылка размера матриц
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int rows_per_proc = n / size;
    
    double* A = NULL;
    double* B = (double*)malloc(n * n * sizeof(double));
    double* C = NULL;
    
    double* local_A = (double*)malloc(rows_per_proc * n * sizeof(double));
    double* local_C = (double*)malloc(rows_per_proc * n * sizeof(double));

    // Инициализация матриц на процессе 0
    if (rank == 0) {
        A = (double*)malloc(n * n * sizeof(double));
        C = (double*)malloc(n * n * sizeof(double));
        
        printf("Matrix A:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i * n + j] = (double)(i + 1);
                printf("%.0f ", A[i * n + j]);
            }
            printf("\n");
        }
        
        printf("\nMatrix B:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                B[i * n + j] = (double)(j + 1);
                printf("%.0f ", B[i * n + j]);
            }
            printf("\n");
        }
    }

    // Рассылка матрицы B всем процессам
    MPI_Bcast(B, n * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Распределение строк матрицы A по процессам
    MPI_Scatter(A, rows_per_proc * n, MPI_DOUBLE, 
                local_A, rows_per_proc * n, MPI_DOUBLE, 
                0, MPI_COMM_WORLD);

    // Вычисление частичного произведения матриц
    for (int i = 0; i < rows_per_proc; i++) {
        for (int j = 0; j < n; j++) {
            local_C[i * n + j] = 0.0;
            for (int k = 0; k < n; k++) {
                local_C[i * n + j] += local_A[i * n + k] * B[k * n + j];
            }
        }
    }

    // Сбор результатов на процессе 0
    MPI_Gather(local_C, rows_per_proc * n, MPI_DOUBLE,
               C, rows_per_proc * n, MPI_DOUBLE,
               0, MPI_COMM_WORLD);

    // Вывод результата на процессе 0
    if (rank == 0) {
        printf("\nMatrix C (A * B):\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%.0f ", C[i * n + j]);
            }
            printf("\n");
        }
        free(A);
        free(C);
    }

    free(B);
    free(local_A);
    free(local_C);

    MPI_Finalize();
    return 0;
}

