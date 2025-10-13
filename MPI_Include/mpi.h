// Упрощенный заголовок MPI для компиляции
// Только для учебных целей - полная версия в Microsoft MPI SDK

#ifndef MPI_INCLUDED
#define MPI_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

// Основные типы данных MPI
typedef int MPI_Comm;
typedef int MPI_Datatype;
typedef int MPI_Op;
typedef int MPI_Request;

typedef struct MPI_Status {
    int MPI_SOURCE;
    int MPI_TAG;
    int MPI_ERROR;
} MPI_Status;

typedef int MPI_Group;
typedef int MPI_Win;
typedef int MPI_Info;
typedef long long MPI_Aint;

// Предопределенные константы
#define MPI_COMM_WORLD ((MPI_Comm)0x44000000)
#define MPI_COMM_NULL ((MPI_Comm)0x04000000)
#define MPI_INT ((MPI_Datatype)0x4c000405)
#define MPI_CHAR ((MPI_Datatype)0x4c000101)
#define MPI_FLOAT ((MPI_Datatype)0x4c00040a)
#define MPI_DOUBLE ((MPI_Datatype)0x4c00080b)
#define MPI_LONG_LONG ((MPI_Datatype)0x4c000809)

#define MPI_SUM ((MPI_Op)0x58000003)
#define MPI_MAX ((MPI_Op)0x58000001)
#define MPI_MIN ((MPI_Op)0x58000002)
#define MPI_PROD ((MPI_Op)0x58000004)

#define MPI_ANY_SOURCE (-1)
#define MPI_ANY_TAG (-1)

#define MPI_SUCCESS 0
#define MPI_STATUSES_IGNORE ((MPI_Status*)1)
#define MPI_STATUS_IGNORE ((MPI_Status*)1)
#define MPI_INFO_NULL ((MPI_Info)0x1c000000)
#define MPI_ARGV_NULL ((char**)0)

// Основные функции MPI
int MPI_Init(int *argc, char ***argv);
int MPI_Finalize(void);
int MPI_Comm_size(MPI_Comm comm, int *size);
int MPI_Comm_rank(MPI_Comm comm, int *rank);
int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status);
int MPI_Isend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Irecv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request);
int MPI_Wait(MPI_Request *request, MPI_Status *status);
int MPI_Waitall(int count, MPI_Request array_of_requests[], MPI_Status array_of_statuses[]);

// Коллективные операции
int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm);
int MPI_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm);
int MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
int MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);

// Группы и коммуникаторы
int MPI_Comm_group(MPI_Comm comm, MPI_Group *group);
int MPI_Group_incl(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup);
int MPI_Group_excl(MPI_Group group, int n, const int ranks[], MPI_Group *newgroup);
int MPI_Group_free(MPI_Group *group);
int MPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm *newcomm);
int MPI_Comm_free(MPI_Comm *comm);

// Динамическое управление процессами
int MPI_Comm_spawn(const char *command, char *argv[], int maxprocs, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *intercomm, int array_of_errcodes[]);
int MPI_Comm_get_parent(MPI_Comm *parent);
int MPI_Comm_disconnect(MPI_Comm *comm);
int MPI_Comm_remote_size(MPI_Comm comm, int *size);

// Односторонние коммуникации
int MPI_Win_create(void *base, MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win *win);
int MPI_Win_free(MPI_Win *win);
int MPI_Win_fence(int assert, MPI_Win win);
int MPI_Put(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win);
int MPI_Get(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win);

#ifdef __cplusplus
}
#endif

#endif // MPI_INCLUDED

