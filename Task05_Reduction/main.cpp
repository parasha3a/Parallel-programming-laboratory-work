// Задание 5. Общие и частные переменные в OpenMP: параметр reduction
// Параллельное вычисление суммы чисел от 1 до N с использованием 2 нитей

#include <iostream>
#include <omp.h>

int main() {
    int N;
    std::cout << "Enter N: ";
    std::cin >> N;

    // Версия 1: 2 нити с if-else распределением (как в методичке)
    std::cout << "\nVersion 1 (2 threads with if-else):" << std::endl;
    long long sum = 0;
    
    #pragma omp parallel num_threads(2) reduction(+:sum)
    {
        int thread_num = omp_get_thread_num();
        
        if (thread_num == 0) {
            // Нить 0: вычисляет сумму от 1 до N/2
            for (int i = 1; i <= N / 2; i++) {
                sum += i;
            }
            std::cout << "[0]: Sum = " << sum << std::endl;
        }
        else {
            // Нить 1: вычисляет сумму от N/2+1 до N
            for (int i = N / 2 + 1; i <= N; i++) {
                sum += i;
            }
            std::cout << "[1]: Sum = " << sum << std::endl;
        }
    }
    
    std::cout << "Sum = " << sum << std::endl;

    // Версия 2: модификация для k нитей
    int k;
    std::cout << "\nEnter number of threads k: ";
    std::cin >> k;
    std::cout << "\nVersion 2 (k threads with dynamic distribution):" << std::endl;
    sum = 0;

    #pragma omp parallel num_threads(k) reduction(+:sum)
    {
        int thread_num = omp_get_thread_num();
        int total_threads = omp_get_num_threads();
        long long partial_sum = 0;
        
        // Каждая нить вычисляет свою часть суммы
        for (int i = thread_num + 1; i <= N; i += total_threads) {
            partial_sum += i;
        }
        
        sum = partial_sum;
        std::cout << "[" << thread_num << "]: Sum = " << partial_sum << std::endl;
    }
    
    std::cout << "Sum = " << sum << std::endl;

    return 0;
}

