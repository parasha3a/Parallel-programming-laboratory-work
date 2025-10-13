#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

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

    // Создание окна для односторонней коммуникации
    MPI_Win win;
    long long* win_buffer = (long long*)malloc(sizeof(long long));
    MPI_Win_create(win_buffer, sizeof(long long), sizeof(long long), 
                   MPI_INFO_NULL, MPI_COMM_WORLD, &win);

    // Процесс 0 размещает N в окнах всех процессов
    if (rank == 0) {
        MPI_Win_fence(0, win);
        for (int i = 1; i < size; i++) {
            MPI_Put(&N, 1, MPI_LONG_LONG, i, 0, 1, MPI_LONG_LONG, win);
        }
        *win_buffer = N;
        MPI_Win_fence(0, win);
    }
    else {
        MPI_Win_fence(0, win);
        MPI_Win_fence(0, win);
    }

    // Вычисление числа π
    double h = 1.0 / (double)(*win_buffer);
    double local_sum = 0.0;

    for (long long i = rank; i < *win_buffer; i += size) {
        double x = h * ((double)i + 0.5);
        local_sum += 4.0 / (1.0 + x * x);
    }

    local_sum *= h;

    // Сбор результатов на процессе 0 с помощью односторонней коммуникации
    double* result_buffer = NULL;
    MPI_Win result_win;
    
    if (rank == 0) {
        result_buffer = (double*)calloc(size, sizeof(double));
    }
    
    MPI_Win_create(result_buffer, (rank == 0 ? size * sizeof(double) : 0), 
                   sizeof(double), MPI_INFO_NULL, MPI_COMM_WORLD, &result_win);

    MPI_Win_fence(0, result_win);
    MPI_Put(&local_sum, 1, MPI_DOUBLE, 0, rank, 1, MPI_DOUBLE, result_win);
    MPI_Win_fence(0, result_win);

    if (rank == 0) {
        double pi = 0.0;
        for (int i = 0; i < size; i++) {
            pi += result_buffer[i];
        }
        printf("Calculated PI = %.8f\n", pi);
        free(result_buffer);
    }

    MPI_Win_free(&result_win);
    MPI_Win_free(&win);
    free(win_buffer);

    MPI_Finalize();
    return 0;
}

