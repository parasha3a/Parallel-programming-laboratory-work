# Решение проблем с MPI проектами

## Проблема: "Файл Task..._MPI_....exe не найден"

Эта ошибка означает, что проект не был собран. 

### Решение:

#### Шаг 1: Установите Microsoft MPI

**Обязательно!** MPI проекты не соберутся без установленного MPI SDK.

1. Скачайте оба файла с https://www.microsoft.com/en-us/download/details.aspx?id=105289:
   - `msmpisetup.exe` (Runtime)
   - `msmpisdk.msi` (SDK)

2. Установите оба файла (сначала Runtime, затем SDK)

3. Проверьте установку:
   ```cmd
   mpiexec -help
   ```
   Должна отобразиться справка по mpiexec.

#### Шаг 2: Соберите проекты в Visual Studio

1. Откройте `OpenMP_Labs.sln` в Visual Studio

2. Выберите конфигурацию **Debug** и платформу **x64**

3. В Solution Explorer щелкните правой кнопкой на **Solution 'OpenMP_Labs'**

4. Выберите **Build Solution** (или нажмите **F7**)

5. Дождитесь завершения сборки (смотрите вкладку Output внизу)

#### Шаг 3: Проверьте результаты сборки

Если сборка прошла успешно, файлы будут здесь:
```
x64\Debug\
├── Task15_MPI_IAm.exe
├── Task16_MPI_FirstSecond.exe
├── Task17_MPI_Send.exe
├── Task18_MPI_Baton.exe
├── Task19_MPI_MasterSlave.exe
└── Task20_MPI_Isend.exe
```

#### Шаг 4: Запустите программу

Теперь можно запустить через bat-файл:
```cmd
cd Task20_MPI_Isend
run.bat
```

---

## Типичные ошибки сборки

### Ошибка: "Cannot open include file: 'mpi.h'"

**Причина**: Не установлен MPI SDK или неправильные пути.

**Решение**:
1. Убедитесь, что установлен `msmpisdk.msi`
2. Проверьте путь: `C:\Program Files\Microsoft MPI\Inc\mpi.h` должен существовать
3. Если MPI установлен в другой папке, измените пути в .vcxproj файлах

### Ошибка: "Cannot open file 'msmpi.lib'"

**Причина**: Не установлен MPI SDK или неправильные пути к библиотекам.

**Решение**:
1. Проверьте путь: `C:\Program Files\Microsoft MPI\Lib\x64\msmpi.lib` должен существовать
2. Если путь другой, обновите в свойствах проекта:
   - Правой кнопкой на проект → Properties
   - Linker → General → Additional Library Directories
   - Измените на правильный путь

### Ошибка: "mpiexec is not recognized"

**Причина**: Не установлен MPI Runtime или путь не в PATH.

**Решение**:
1. Установите `msmpisetup.exe`
2. Проверьте, что `C:\Program Files\Microsoft MPI\Bin` существует
3. Перезапустите Visual Studio после установки

---

## Быстрая проверка установки MPI

Выполните в командной строке:

```cmd
where mpiexec
dir "C:\Program Files\Microsoft MPI\Inc\mpi.h"
dir "C:\Program Files\Microsoft MPI\Lib\x64\msmpi.lib"
```

Все три команды должны найти файлы. Если нет - переустановите MPI.

---

## Альтернативный запуск (без bat-файла)

Если bat-файл не работает, запустите вручную:

```cmd
cd "C:\Parallel and multithreaded programming"
"C:\Program Files\Microsoft MPI\Bin\mpiexec.exe" -np 2 "x64\Debug\Task20_MPI_Isend.exe"
```

Где:
- `-np 2` - количество процессов (измените по необходимости)
- Последний аргумент - полный путь к exe файлу

---

## Сборка только одного проекта

Если не хотите собирать все 17 проектов:

1. В Solution Explorer щелкните правой кнопкой на нужном проекте (например, Task20_MPI_Isend)
2. Выберите **Build** (не Build Solution)
3. Дождитесь завершения
4. Запустите bat-файл этого проекта

---

## Проверка версии MPI

```cmd
"C:\Program Files\Microsoft MPI\Bin\mpiexec.exe" -version
```

Должна быть версия 10.0 или выше.

---

## Если ничего не помогает

1. Удалите папку `x64` полностью
2. В Visual Studio: Build → Clean Solution
3. Переустановите Microsoft MPI (оба компонента)
4. Перезапустите Visual Studio
5. Build → Rebuild Solution
6. Попробуйте запустить снова

---

## Контакты для помощи

Если проблема не решается:
1. Проверьте логи сборки (View → Output → показать вывод Build)
2. Скопируйте текст ошибки
3. Проверьте INSTALL_MPI.md для детальных инструкций

