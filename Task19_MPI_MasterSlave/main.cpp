// Задание 19. Коммуникации "точка-точка": схема "мастер-рабочие"
// Slave-процессы отправляют сообщения master-процессу

#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[]) {
    // Инициализация MPI
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int buf;  // Буфер для сообщений
    MPI_Status status;

    if (rank == 0) {
        // Master-процесс (процесс 0)
        std::cout << "Master process: waiting for messages from slaves..." << std::endl;
        
        // Получение сообщений от всех slave-процессов
        for (int src = 1; src < size; src++) {
            MPI_Recv(&buf, 1, MPI_INT, src, 0, MPI_COMM_WORLD, &status);
            std::cout << "Master: receive message '" << buf << "' from process " << src << std::endl;
        }
        
        std::cout << "Master process: all messages received!" << std::endl;
    }
    else {
        // Slave-процессы (все процессы кроме 0)
        buf = rank;  // Каждый slave отправляет свой номер
        
        std::cout << "Slave process " << rank << ": sending message '" << buf << "' to master" << std::endl;
        
        // Отправка сообщения master-процессу
        MPI_Send(&buf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    // Завершение MPI
    MPI_Finalize();

    return 0;
}

