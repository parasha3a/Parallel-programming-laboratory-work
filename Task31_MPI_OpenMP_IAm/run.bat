@echo off
set OMP_NUM_THREADS=3
mpiexec -n 2 ..\x64\Debug\Task31_MPI_OpenMP_IAm.exe
pause

