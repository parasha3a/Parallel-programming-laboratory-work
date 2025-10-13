// Задание 4. Общие и частные переменные в OpenMP: программа "Скрытая синхронизация"
// Демонстрация работы shared и private переменных

#include <iostream>
#include <omp.h>
#include <Windows.h>

int main() {
    int k;
    std::cout << "Enter number of threads: ";
    std::cin >> k;

    omp_set_num_threads(k);

    int rank;

    // Версия 1: rank как общая переменная (shared) - без задержки
    std::cout << "\nVersion 1 (shared variable, no delay):" << std::endl;
    rank = omp_get_thread_num();
    std::cout << "Initial rank value: " << rank << std::endl;

    #pragma omp parallel shared(rank)
    {
        rank = omp_get_thread_num();
        std::cout << "I am " << rank << " thread." << std::endl;
    }

    // Версия 2: rank как общая переменная (shared) - с задержкой (демонстрация ошибки)
    std::cout << "\nVersion 2 (shared variable, with delay - race condition!):" << std::endl;
    
    #pragma omp parallel shared(rank)
    {
        rank = omp_get_thread_num();
        Sleep(100); // Имитация длительных вычислений
        std::cout << "I am " << rank << " thread." << std::endl;
    }

    // Версия 3: rank как частная переменная (private) - корректная работа
    std::cout << "\nVersion 3 (private variable - correct!):" << std::endl;
    
    #pragma omp parallel private(rank)
    {
        rank = omp_get_thread_num();
        Sleep(100); // Имитация длительных вычислений
        std::cout << "I am " << rank << " thread." << std::endl;
    }

    return 0;
}

