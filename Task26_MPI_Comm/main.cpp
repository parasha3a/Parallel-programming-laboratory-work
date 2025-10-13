#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Group oldgroup, group;
    MPI_Comm newcomm = MPI_COMM_NULL;

    // Получаем группу из MPI_COMM_WORLD
    MPI_Comm_group(MPI_COMM_WORLD, &oldgroup);

    // Создаем массив рангов четных процессов
    int even_count = (size + 1) / 2;
    int* ranks = (int*)malloc(even_count * sizeof(int));
    
    int idx = 0;
    for (int i = 0; i < size; i += 2) {
        ranks[idx++] = i;
    }

    // Создаем новую группу из четных процессов
    MPI_Group_incl(oldgroup, even_count, ranks, &group);

    // Создаем новый коммуникатор для этой группы
    MPI_Comm_create(MPI_COMM_WORLD, group, &newcomm);

    int newrank = -1;
    int newsize = 0;
    char message[100] = "no";

    // Определяем ранг и размер в новом коммуникаторе
    if (newcomm != MPI_COMM_NULL) {
        MPI_Comm_rank(newcomm, &newrank);
        MPI_Comm_size(newcomm, &newsize);

        // Процесс 0 нового коммуникатора получает сообщение
        if (newrank == 0) {
            strcpy_s(message, 100, "A");
        }

        // Рассылка сообщения внутри нового коммуникатора
        MPI_Bcast(message, 100, MPI_CHAR, 0, newcomm);
    }

    // Вывод информации
    printf("MPI_COMM_WORLD: %d from %d. New comm: %d from %d. Message = %s\n",
           rank, size, newrank, newsize, message);

    // Освобождение ресурсов
    MPI_Group_free(&group);
    MPI_Group_free(&oldgroup);
    
    if (newcomm != MPI_COMM_NULL) {
        MPI_Comm_free(&newcomm);
    }

    free(ranks);

    MPI_Finalize();
    return 0;
}

