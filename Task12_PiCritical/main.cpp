// Задание 12. Гонка потоков в OpenMP: программа "Число π" с critical
// Вычисление числа π без reduction, с использованием директивы critical

#include <iostream>
#include <iomanip>
#include <omp.h>

int main() {
    long long N;
    std::cout << "Enter N (precision): ";
    std::cin >> N;

    double pi = 0.0;

    std::cout << "\nProcessing with critical directive:" << std::endl;

    // Использование critical для безопасного обновления pi
    #pragma omp parallel
    {
        double x_i;
        int thread_num = omp_get_thread_num();
        int total_threads = omp_get_num_threads();
        
        // Каждая нить вычисляет свою частичную сумму
        double partial_sum = 0.0;
        for (long long i = thread_num; i < N; i += total_threads) {
            x_i = (i + 0.5) / N;
            partial_sum += 1.0 / (1.0 + x_i * x_i);
        }
        
        // critical гарантирует, что только одна нить одновременно обновляет pi
        #pragma omp critical
        {
            pi += partial_sum;
            std::cout << "[" << thread_num << "]: partial sum = " << partial_sum << std::endl;
        }
    }
    
    pi *= 4.0 / N;

    std::cout << "\n[Final result]:" << std::endl;
    std::cout << std::fixed << std::setprecision(8);
    std::cout << "Pi = " << pi << std::endl;

    return 0;
}

