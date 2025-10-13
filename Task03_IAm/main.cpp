// Задание 3. Программа "I am!"
// Каждая нить выводит свой номер и общее количество нитей

#include <iostream>
#include <omp.h>

int main() {
    int k;
    std::cout << "Enter number of threads: ";
    std::cin >> k;

    // Устанавливаем количество нитей
    omp_set_num_threads(k);

    // Версия 1: каждая нить выводит свой номер и количество нитей
    std::cout << "\nVersion 1 (each thread prints its info):" << std::endl;
    #pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        int total_threads = omp_get_num_threads();
        std::cout << "I am " << thread_num << " thread from " << total_threads << " threads!" << std::endl;
    }

    // Версия 2: модификация - каждая нить выводит информацию с четным номером
    std::cout << "\nVersion 2 (only even thread numbers):" << std::endl;
    #pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        int total_threads = omp_get_num_threads();
        if (thread_num % 2 == 0) {
            std::cout << "I am " << thread_num << " thread from " << total_threads << " threads!" << std::endl;
        }
    }

    return 0;
}

