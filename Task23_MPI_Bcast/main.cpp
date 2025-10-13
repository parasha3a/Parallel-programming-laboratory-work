#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = 0;
    char buf[100];

    // Процесс 0 вводит данные
    if (rank == 0) {
        printf("Enter string length (1 <= n <= 100): ");
        scanf_s("%d", &n);
        printf("Enter string: ");
        scanf_s("%s", buf, 100);
    }

    // Широковещательная рассылка длины строки
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Широковещательная рассылка строки
    MPI_Bcast(buf, 100, MPI_CHAR, 0, MPI_COMM_WORLD);

    // Каждый процесс обрабатывает свои буквы алфавита
    char a = 'a';

    for (int i = rank; i < 26; i += size) {
        char target = (char)((int)a + i);
        int count = 0;
        
        // Подсчет вхождений буквы
        for (int j = 0; j < n; j++) {
            if (buf[j] == target) {
                count++;
            }
        }
        
        // Вывод результата для этой буквы
        printf("%c = %d\n", target, count);
    }

    MPI_Finalize();
    return 0;
}

