// Задание 10. Параллельные секции в OpenMP: программа "I'm here"
// Использование директив sections и section для создания параллельных секций

#include <iostream>
#include <omp.h>

int main() {
    int k;
    std::cout << "Enter number of threads: ";
    std::cin >> k;

    omp_set_num_threads(k);

    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                int thread_num = omp_get_thread_num();
                std::cout << "[" << thread_num << "]: came in section 1" << std::endl;
            }

            #pragma omp section
            {
                int thread_num = omp_get_thread_num();
                std::cout << "[" << thread_num << "]: came in section 2" << std::endl;
            }

            #pragma omp section
            {
                int thread_num = omp_get_thread_num();
                std::cout << "[" << thread_num << "]: came in section 3" << std::endl;
            }

            #pragma omp section
            {
                int thread_num = omp_get_thread_num();
                std::cout << "[" << thread_num << "]: came in section 4" << std::endl;
            }
        }

        // Каждая нить после выхода из секций выводит сообщение
        int thread_num = omp_get_thread_num();
        std::cout << "[" << thread_num << "]: parallel region" << std::endl;
    }

    return 0;
}

