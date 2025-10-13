@echo off
REM Запуск MPI программы Task15_MPI_IAm

SET EXE_PATH=%~dp0..\x64\Debug\Task15_MPI_IAm.exe

IF NOT EXIST "%EXE_PATH%" (
    echo ERROR: Файл не найден: %EXE_PATH%
    echo.
    echo Пожалуйста, сначала соберите проект Task15_MPI_IAm в Visual Studio:
    echo 1. Откройте OpenMP_Labs.sln
    echo 2. Выберите Task15_MPI_IAm в Solution Explorer
    echo 3. Build -^> Build Solution ^(F7^)
    echo.f
    pause
    exit /b 1
)

"C:\Program Files\Microsoft MPI\Bin\mpiexec.exe" -np 3 "%EXE_PATH%"

pause

