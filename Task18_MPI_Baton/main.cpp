// Задание 18. Коммуникации "точка-точка": схема "эстафетная палочка"
// Последовательная передача сообщения от процесса к процессу

#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[]) {
    // Инициализация MPI
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int buf;  // Буфер для "эстафетной палочки"
    MPI_Status status;

    if (rank == 0) {
        // Процесс 0 инициирует передачу
        buf = 0;
        std::cout << "[" << rank << "]: sending message '" << buf << "'" << std::endl;
        
        // Отправка следующему процессу (1)
        MPI_Send(&buf, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        
        // Ожидание сообщения от последнего процесса (size-1)
        MPI_Recv(&buf, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, &status);
        std::cout << "[" << rank << "]: receive message '" << buf << "'" << std::endl;
    }
    else {
        // Остальные процессы
        
        // Прием сообщения от предыдущего процесса
        MPI_Recv(&buf, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
        std::cout << "[" << rank << "]: receive message '" << buf << "'" << std::endl;
        
        // Увеличение значения "палочки"
        buf++;
        
        // Определение следующего процесса (циклически)
        int next_rank = (rank + 1) % size;
        
        std::cout << "[" << rank << "]: sending message '" << buf << "'" << std::endl;
        MPI_Send(&buf, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD);
    }

    // Вывод финального значения палочки
    std::cout << "[" << rank << "]: final value = " << buf << std::endl;

    // Завершение MPI
    MPI_Finalize();

    return 0;
}

