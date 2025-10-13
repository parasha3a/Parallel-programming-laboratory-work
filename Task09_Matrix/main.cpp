// Задание 9. Распараллеливание циклов в OpenMP: программа "Матрица"
// Параллельное вычисление произведения двух матриц A × B = C

#include <iostream>
#include <vector>
#include <omp.h>

int main() {
    int n;
    std::cout << "Enter matrix size n (1 <= n <= 10): ";
    std::cin >> n;

    // Создание матриц A, B и C
    std::vector<std::vector<double>> A(n, std::vector<double>(n));
    std::vector<std::vector<double>> B(n, std::vector<double>(n));
    std::vector<std::vector<double>> C(n, std::vector<double>(n, 0.0));

    // Ввод матрицы A
    std::cout << "Enter matrix A (" << n << "x" << n << "):" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> A[i][j];
        }
    }

    // Ввод матрицы B
    std::cout << "Enter matrix B (" << n << "x" << n << "):" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> B[i][j];
        }
    }

    // Параллельное умножение матриц
    // C[i][m] = sum(A[i][j] * B[j][m]) for j = 0..n-1
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int m = 0; m < n; m++) {
            double sum = 0.0;
            for (int j = 0; j < n; j++) {
                sum += A[i][j] * B[j][m];
            }
            C[i][m] = sum;
        }
    }

    // Вывод результата
    std::cout << "\nResult matrix C (A x B):" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << C[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}







