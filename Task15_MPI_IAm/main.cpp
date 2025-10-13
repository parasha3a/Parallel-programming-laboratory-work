// Задание 15. Программа "I am!" на MPI
// Каждый процесс выводит свой номер и общее количество процессов

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

    // Вывод информации о процессе
    std::cout << "I am " << rank << " process from " << size << " processes!" << std::endl;

    // Завершение MPI
    MPI_Finalize();

    return 0;
}

