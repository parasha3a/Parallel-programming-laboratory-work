// Задание 20. Коммуникации "точка-точка": простые неблокирующие обмены
// Использование MPI_Isend и MPI_Irecv для неблокирующей передачи

#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[]) {
    // Инициализация MPI
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int buf;  // Буфер для сообщения
    MPI_Request request;  // Идентификатор для асинхронных операций
    MPI_Status status;

    if (rank == 0) {
        // Процесс 0 отправляет сообщение
        buf = 45;  // Значение для отправки
        std::cout << "Process 0: initiating send of message '" << buf << "'" << std::endl;
        
        // Неблокирующая отправка сообщения процессу 1
        MPI_Isend(&buf, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
        
        std::cout << "Process 0: send initiated, doing other work..." << std::endl;
        
        // Здесь можно выполнять другие операции...
        
        // Ожидание завершения отправки
        MPI_Wait(&request, &status);
        std::cout << "Process 0: send completed!" << std::endl;
    }
    else if (rank == 1) {
        // Процесс 1 получает сообщение
        std::cout << "Process 1: initiating receive..." << std::endl;
        
        // Неблокирующий прием сообщения от процесса 0
        MPI_Irecv(&buf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        
        std::cout << "Process 1: receive initiated, doing other work..." << std::endl;
        
        // Здесь можно выполнять другие операции...
        
        // Ожидание завершения приема
        MPI_Wait(&request, &status);
        std::cout << "Process 1: receive message '" << buf << "'" << std::endl;
    }

    // Завершение MPI
    MPI_Finalize();

    return 0;
}

