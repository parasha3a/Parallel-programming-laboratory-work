@echo off
chcp 65001 >nul
echo ======================================
echo Task29: Исследование масштабируемости MPI-программ
echo ======================================
echo.
echo Введите количество процессов (по умолчанию 4):
set /p NPROCS=
if "%NPROCS%"=="" set NPROCS=4

echo.
echo Запуск с %NPROCS% процессами...
echo.

"C:\Program Files\Microsoft MPI\Bin\mpiexec.exe" -np %NPROCS% "..\x64\Debug\Task29_MPI_Scalability.exe"

echo.
echo ======================================
echo Готово!
echo ======================================
pause

