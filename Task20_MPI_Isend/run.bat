@echo off
REM Запуск MPI программы Task20_MPI_Isend (неблокирующие обмены)

SET EXE_PATH=%~dp0..\x64\Debug\Task20_MPI_Isend.exe

IF NOT EXIST "%EXE_PATH%" (
    echo ERROR: Файл не найден: %EXE_PATH%
    echo.
    echo Пожалуйста, сначала соберите проект Task20_MPI_Isend в Visual Studio:
    echo 1. Откройте OpenMP_Labs.sln
    echo 2. Выберите Task20_MPI_Isend
    echo 3. Build -^> Build Solution ^(F7^)
    echo.
    pause
    exit /b 1
)

"C:\Program Files\Microsoft MPI\Bin\mpiexec.exe" -np 2 "%EXE_PATH%"

pause

