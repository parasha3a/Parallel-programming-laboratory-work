#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int send_to = (rank + 1) % size;     // Следующий процесс
    int recv_from = (rank - 1 + size) % size;  // Предыдущий процесс

    int send_data = rank;
    int recv_data = -1;

    MPI_Request send_request, recv_request;
    MPI_Status status;

    // Неблокирующая отправка следующему процессу
    printf("[%d]: sending to %d\n", rank, send_to);
    MPI_Isend(&send_data, 1, MPI_INT, send_to, 0, MPI_COMM_WORLD, &send_request);

    // Неблокирующий прием от предыдущего процесса
    printf("[%d]: receiving from %d\n", rank, recv_from);
    MPI_Irecv(&recv_data, 1, MPI_INT, recv_from, 0, MPI_COMM_WORLD, &recv_request);

    // Ожидание завершения операций
    MPI_Wait(&send_request, &status);
    MPI_Wait(&recv_request, &status);

    printf("[%d]: receive message '%d'\n", rank, recv_data);

    MPI_Finalize();
    return 0;
}

