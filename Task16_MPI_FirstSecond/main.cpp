// Задание 16. Программа "На первый-второй рассчитайся!" на MPI
// Процессы с четным номером выводят "SECOND", с нечетным - "FIRST"

#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[]) {
    // Инициализация MPI
    MPI_Init(&argc, &argv);

    int rank;  // Номер текущего процесса
    int size;  // Общее количество процессов

    // Получение номера процесса
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Получение количества процессов
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Распределение процессов по типам
    if (rank == 0) {
        // Процесс 0 выводит общее количество процессов
        std::cout << size << " processes." << std::endl;
    }
    else if (rank % 2 == 0) {
        // Четные процессы (кроме 0)
        std::cout << "I am " << rank << " process: SECOND!" << std::endl;
    }
    else {
        // Нечетные процессы
        std::cout << "I am " << rank << " process: FIRST!" << std::endl;
    }

    // Завершение MPI
    MPI_Finalize();

    return 0;
}

