// Задание 7. Распараллеливание циклов в OpenMP: параметр schedule
// Исследование влияния различных режимов schedule на распределение итераций

#include <iostream>
#include <iomanip>
#include <omp.h>

void test_schedule(const char* schedule_type, int k, int N) {
    std::cout << "\n" << schedule_type << ":" << std::endl;
    
    int iteration_thread[10]; // Для хранения номера нити для каждой итерации
    
    if (std::string(schedule_type) == "static") {
        #pragma omp parallel for schedule(static) num_threads(k)
        for (int i = 0; i < N; i++) {
            iteration_thread[i] = omp_get_thread_num();
        }
    }
    else if (std::string(schedule_type) == "static,1") {
        #pragma omp parallel for schedule(static, 1) num_threads(k)
        for (int i = 0; i < N; i++) {
            iteration_thread[i] = omp_get_thread_num();
        }
    }
    else if (std::string(schedule_type) == "static,2") {
        #pragma omp parallel for schedule(static, 2) num_threads(k)
        for (int i = 0; i < N; i++) {
            iteration_thread[i] = omp_get_thread_num();
        }
    }
    else if (std::string(schedule_type) == "dynamic") {
        #pragma omp parallel for schedule(dynamic) num_threads(k)
        for (int i = 0; i < N; i++) {
            iteration_thread[i] = omp_get_thread_num();
        }
    }
    else if (std::string(schedule_type) == "dynamic,2") {
        #pragma omp parallel for schedule(dynamic, 2) num_threads(k)
        for (int i = 0; i < N; i++) {
            iteration_thread[i] = omp_get_thread_num();
        }
    }
    else if (std::string(schedule_type) == "guided") {
        #pragma omp parallel for schedule(guided) num_threads(k)
        for (int i = 0; i < N; i++) {
            iteration_thread[i] = omp_get_thread_num();
        }
    }
    else if (std::string(schedule_type) == "guided,2") {
        #pragma omp parallel for schedule(guided, 2) num_threads(k)
        for (int i = 0; i < N; i++) {
            iteration_thread[i] = omp_get_thread_num();
        }
    }
    
    // Вывод результата
    for (int i = 0; i < N; i++) {
        std::cout << "[" << i + 1 << "]: calculation of the iteration number " << i + 1 
                  << " - thread " << iteration_thread[i] << std::endl;
    }
}

int main() {
    const int k = 4;  // количество нитей
    const int N = 10; // количество итераций

    std::cout << "Schedule parameter testing (k=" << k << ", N=" << N << ")" << std::endl;
    std::cout << "===================================================" << std::endl;

    test_schedule("static", k, N);
    test_schedule("static,1", k, N);
    test_schedule("static,2", k, N);
    test_schedule("dynamic", k, N);
    test_schedule("dynamic,2", k, N);
    test_schedule("guided", k, N);
    test_schedule("guided,2", k, N);

    return 0;
}







