@echo off
REM Запуск MPI программы Task17_MPI_Send

SET EXE_PATH=%~dp0..\x64\Debug\Task17_MPI_Send.exe

IF NOT EXIST "%EXE_PATH%" (
    echo ERROR: Файл не найден: %EXE_PATH%
    echo.
    echo Пожалуйста, сначала соберите проект в Visual Studio ^(F7^)
    echo.
    pause
    exit /b 1
)

"C:\Program Files\Microsoft MPI\Bin\mpiexec.exe" -np 2 "%EXE_PATH%"

pause

