// Задание 17. Коммуникации "точка-точка": простые блокирующие обмены
// Процесс 0 отправляет сообщение процессу 1

#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[]) {
    // Инициализация MPI
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int buf;  // Буфер для сообщения

    if (rank == 0) {
        // Процесс 0 отправляет сообщение
        buf = 45;  // Значение для отправки
        std::cout << "Process 0: sending message '" << buf << "'" << std::endl;
        
        // Блокирующая отправка сообщения процессу 1
        MPI_Send(&buf, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    else if (rank == 1) {
        // Процесс 1 получает сообщение
        MPI_Status status;
        
        // Блокирующий прием сообщения от процесса 0
        MPI_Recv(&buf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        
        std::cout << "Process 1: receive message '" << buf << "'" << std::endl;
    }

    // Завершение MPI
    MPI_Finalize();

    return 0;
}

