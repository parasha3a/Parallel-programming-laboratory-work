@echo off
chcp 65001 >nul
echo ======================================
echo Task30: Проект с поддержкой MPI и OpenMP
echo ======================================
echo.
echo Запуск с 2 процессами...
echo.

"C:\Program Files\Microsoft MPI\Bin\mpiexec.exe" -np 2 "..\x64\Debug\Task30_MPI_OpenMP_Project.exe"

echo.
echo ======================================
echo Готово!
echo ======================================
pause

