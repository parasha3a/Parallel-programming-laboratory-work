// Задание 2. Многопоточная программа "Hello World!"
// Создается 4 нити, каждая выводит "Hello World!"

#include <iostream>
#include <omp.h>

int main() {
    // Устанавливаем количество нитей равным 4
    omp_set_num_threads(4);

    // Параллельная область - каждая нить выполняет этот блок
    #pragma omp parallel
    {
        std::cout << "Hello World!" << std::endl;
    }

    return 0;
}







