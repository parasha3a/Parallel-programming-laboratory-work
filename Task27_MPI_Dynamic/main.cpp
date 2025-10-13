#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    int rank, size;
    MPI_Comm parent_comm, inter_comm;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Проверяем, является ли процесс порожденным
    MPI_Comm_get_parent(&parent_comm);
    
    if (parent_comm == MPI_COMM_NULL) {
        // Родительский процесс
        int n;
        printf("Enter number of child processes to spawn: ");
        scanf_s("%d", &n);
        
        printf("I am %d process from %d processes! My parent is none.\n", rank, size);
        
        // Динамическое создание дочерних процессов
        int* errcodes = (int*)malloc(n * sizeof(int));
        
        MPI_Comm_spawn(argv[0], MPI_ARGV_NULL, n, MPI_INFO_NULL, 
                      0, MPI_COMM_WORLD, &inter_comm, errcodes);
        
        // Отправка сообщения дочерним процессам
        for (int i = 0; i < n; i++) {
            char msg[100];
            sprintf_s(msg, 100, "Hello from parent %d", rank);
            MPI_Send(msg, 100, MPI_CHAR, i, 0, inter_comm);
        }
        
        printf("Parent process %d: spawned %d child processes\n", rank, n);
        
        free(errcodes);
        MPI_Comm_disconnect(&inter_comm);
    }
    else {
        // Дочерний процесс
        char msg[100];
        MPI_Status status;
        
        // Получение сообщения от родителя
        MPI_Recv(msg, 100, MPI_CHAR, 0, 0, parent_comm, &status);
        
        // Узнаем ранг родителя
        int parent_rank;
        MPI_Comm_remote_size(parent_comm, &parent_rank);
        
        printf("I am %d process from %d processes! My parent is 0.\n", rank, size);
        printf("Child process %d received: %s\n", rank, msg);
        
        MPI_Comm_disconnect(&parent_comm);
    }
    
    MPI_Finalize();
    return 0;
}

