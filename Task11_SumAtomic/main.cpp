// Задание 11. Гонка потоков в OpenMP: программа "Сумма чисел" с atomic
// Вычисление суммы от 1 до N без reduction, с использованием директивы atomic

#include <iostream>
#include <omp.h>

int main() {
    int k, N;
    std::cout << "Enter number of threads: ";
    std::cin >> k;
    std::cout << "Enter N: ";
    std::cin >> N;

    omp_set_num_threads(k);

    long long sum = 0;

    std::cout << "\nProcessing with atomic directive:" << std::endl;

    // Использование atomic для безопасного обновления sum
    #pragma omp parallel for
    for (int i = 1; i <= N; i++) {
        int thread_num = omp_get_thread_num();
        
        // atomic гарантирует атомарность операции инкремента
        #pragma omp atomic
        sum += i;
        
        #pragma omp critical
        {
            std::cout << "[" << thread_num << "]: processing iteration " << i 
                      << ", sum = " << sum << std::endl;
        }
    }

    std::cout << "\n[Final result]:" << std::endl;
    std::cout << "Sum = " << sum << std::endl;

    return 0;
}

