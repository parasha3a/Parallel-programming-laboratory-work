// Задание 8. Распараллеливание циклов в OpenMP: программа "Число π"
// Вычисление числа π с точностью до N знаков после запятой

#include <iostream>
#include <iomanip>
#include <cmath>
#include <omp.h>

int main() {
    long long N;
    std::cout << "Enter N (precision): ";
    std::cin >> N;

    double pi = 0.0;
    double x_i;

    // Формула: π = 4 * sum(1/(1+x_i^2) * 1/N), где x_i = (i + 0.5) / N, i = 0..N-1
    #pragma omp parallel for private(x_i) reduction(+:pi)
    for (long long i = 0; i < N; i++) {
        x_i = (i + 0.5) / N;
        pi += 1.0 / (1.0 + x_i * x_i);
    }
    
    pi *= 4.0 / N;

    std::cout << std::fixed << std::setprecision(8);
    std::cout << "Pi = " << pi << std::endl;

    return 0;
}







