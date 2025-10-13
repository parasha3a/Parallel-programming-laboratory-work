// Задание 6. Распараллеливание циклов в OpenMP: программа "Сумма чисел"
// Распределение работы по циклу с помощью директивы for

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

    std::cout << "\nProcessing iterations:" << std::endl;

    // Директива for автоматически распределяет итерации цикла между нитями
    #pragma omp parallel for reduction(+:sum)
    for (int i = 1; i <= N; i++) {
        int thread_num = omp_get_thread_num();
        
        // Вывод информации о том, какая нить обрабатывает итерацию
        #pragma omp critical
        {
            std::cout << "[" << thread_num << "]: processing iteration " << i << std::endl;
        }
        
        sum += i;
    }

    std::cout << "\n[Final result]:" << std::endl;
    std::cout << "Sum = " << sum << std::endl;

    return 0;
}

