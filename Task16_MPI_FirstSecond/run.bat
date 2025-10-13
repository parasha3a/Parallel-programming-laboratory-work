@echo off
REM Запуск MPI программы Task16_MPI_FirstSecond

SET EXE_PATH=%~dp0..\x64\Debug\Task16_MPI_FirstSecond.exe

IF NOT EXIST "%EXE_PATH%" (
    echo ERROR: Файл не найден: %EXE_PATH%
    echo.
    echo Пожалуйста, сначала соберите проект в Visual Studio ^(F7^)
    echo.
    pause
    exit /b 1
)

"C:\Program Files\Microsoft MPI\Bin\mpiexec.exe" -np 4 "%EXE_PATH%"

pause

