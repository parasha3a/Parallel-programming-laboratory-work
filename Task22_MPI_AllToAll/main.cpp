#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Буферы для отправки и приема
    int* send_buf = (int*)malloc(size * sizeof(int));
    int* recv_buf = (int*)malloc(size * sizeof(int));
    
    // Массивы запросов для неблокирующих операций
    MPI_Request* send_requests = (MPI_Request*)malloc((size - 1) * sizeof(MPI_Request));
    MPI_Request* recv_requests = (MPI_Request*)malloc((size - 1) * sizeof(MPI_Request));

    // Инициализация буфера отправки
    for (int i = 0; i < size; i++) {
        send_buf[i] = rank;
    }
    recv_buf[rank] = rank;  // Сам себе

    // Цикл неблокирующих отправок
    int send_idx = 0;
    for (int i = 0; i < size; i++) {
        if (i != rank) {
            printf("[%d]: sending to %d\n", rank, i);
            MPI_Isend(&send_buf[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD, &send_requests[send_idx++]);
        }
    }

    // Ожидание завершения всех отправок
    MPI_Waitall(size - 1, send_requests, MPI_STATUSES_IGNORE);

    // Цикл неблокирующих приемов
    int recv_idx = 0;
    for (int i = 0; i < size; i++) {
        if (i != rank) {
            printf("[%d]: receiving from %d\n", rank, i);
            MPI_Irecv(&recv_buf[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD, &recv_requests[recv_idx++]);
        }
    }

    // Ожидание завершения всех приемов
    MPI_Waitall(size - 1, recv_requests, MPI_STATUSES_IGNORE);

    // Вывод результатов
    for (int i = 0; i < size; i++) {
        printf("[%d]: receive message '%d' from %d\n", rank, recv_buf[i], i);
    }

    free(send_buf);
    free(recv_buf);
    free(send_requests);
    free(recv_requests);

    MPI_Finalize();
    return 0;
}

