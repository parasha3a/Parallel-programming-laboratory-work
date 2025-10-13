@echo off
set OMP_NUM_THREADS=4
mpiexec -n 2 ..\x64\Debug\Task32_MPI_OpenMP_Pi.exe
pause

