# Лабораторные работы по параллельному программированию

Проект содержит реализацию заданий по технологиям OpenMP и MPI на C++:
- **OpenMP** (задания 2-12): многопоточное программирование с общей памятью
- **MPI** (задания 15-20): параллельное программирование с передачей сообщений

## Структура проекта

```
OpenMP_Labs/
├── OpenMP_Labs.sln              # Solution файл для Visual Studio
├── Task02_HelloWorld/           # Задание 2: Hello World
│   ├── main.cpp
│   └── Task02_HelloWorld.vcxproj
├── Task03_IAm/                  # Задание 3: I am!
│   ├── main.cpp
│   └── Task03_IAm.vcxproj
├── Task04_SharedPrivate/        # Задание 4: Скрытая синхронизация
│   ├── main.cpp
│   └── Task04_SharedPrivate.vcxproj
├── Task05_Reduction/            # Задание 5: Параметр reduction
│   ├── main.cpp
│   └── Task05_Reduction.vcxproj
├── Task06_ForLoop/              # Задание 6: Распараллеливание циклов
│   ├── main.cpp
│   └── Task06_ForLoop.vcxproj
├── Task07_Schedule/             # Задание 7: Параметр schedule
│   ├── main.cpp
│   └── Task07_Schedule.vcxproj
├── Task08_Pi/                   # Задание 8: Число π
│   ├── main.cpp
│   └── Task08_Pi.vcxproj
├── Task09_Matrix/               # Задание 9: Умножение матриц
│   ├── main.cpp
│   └── Task09_Matrix.vcxproj
├── Task10_Sections/             # Задание 10: Параллельные секции
│   ├── main.cpp
│   └── Task10_Sections.vcxproj
├── Task11_SumAtomic/            # Задание 11: Сумма чисел с atomic
│   ├── main.cpp
│   └── Task11_SumAtomic.vcxproj
├── Task12_PiCritical/           # Задание 12: Число π с critical
│   ├── main.cpp
│   └── Task12_PiCritical.vcxproj
├── Task15_MPI_IAm/              # Задание 15: MPI I am
│   ├── main.cpp
│   ├── run.bat
│   └── Task15_MPI_IAm.vcxproj
├── Task16_MPI_FirstSecond/      # Задание 16: MPI First-Second
│   ├── main.cpp
│   ├── run.bat
│   └── Task16_MPI_FirstSecond.vcxproj
├── Task17_MPI_Send/             # Задание 17: MPI Send (блокирующий)
│   ├── main.cpp
│   ├── run.bat
│   └── Task17_MPI_Send.vcxproj
├── Task18_MPI_Baton/            # Задание 18: MPI Эстафетная палочка
│   ├── main.cpp
│   ├── run.bat
│   └── Task18_MPI_Baton.vcxproj
├── Task19_MPI_MasterSlave/      # Задание 19: MPI Master-Slave
│   ├── main.cpp
│   ├── run.bat
│   └── Task19_MPI_MasterSlave.vcxproj
└── Task20_MPI_Isend/            # Задание 20: MPI Isend (неблокирующий)
    ├── main.cpp
    ├── run.bat
    └── Task20_MPI_Isend.vcxproj
```

## Требования

- **Visual Studio 2019** или новее (с поддержкой C++14 и выше)
- **Поддержка OpenMP** (включена в Visual Studio по умолчанию)
- **Microsoft MPI** (для заданий 15-32) - [Скачать MS-MPI](https://www.microsoft.com/en-us/download/details.aspx?id=105289)
- **Windows 10** или выше

> ⚠️ **Важно:** После клонирования репозитория см. [SETUP.md](SETUP.md) для инструкций по установке MPI и настройке путей.

## Сборка и запуск

### Через Visual Studio (рекомендуется)

1. Откройте файл `OpenMP_Labs.sln` в Visual Studio
2. Выберите конфигурацию сборки (Debug или Release)
3. Выберите платформу x64
4. Выберите нужный проект в Solution Explorer
5. Нажмите **Ctrl+F5** для запуска без отладки или **F5** для запуска с отладкой

### Через командную строку MSBuild

```powershell
# Сборка всего solution
msbuild OpenMP_Labs.sln /p:Configuration=Release /p:Platform=x64

# Сборка конкретного проекта
msbuild Task02_HelloWorld\Task02_HelloWorld.vcxproj /p:Configuration=Release /p:Platform=x64

# Запуск
.\x64\Release\Task02_HelloWorld.exe
```

## Описание заданий

---

## Задания OpenMP (2-12)

### Задание 2: Hello World
**Файл**: `Task02_HelloWorld/main.cpp`

Создается 4 нити, каждая выводит "Hello World!".

**Входные данные**: нет  
**Выходные данные**: 4 строки "Hello World!"

---

### Задание 3: I am!
**Файл**: `Task03_IAm/main.cpp`

Программа создает k нитей, каждая выводит свой номер и общее количество нитей.

**Входные данные**: k - количество нитей  
**Выходные данные**: k строк вида "I am \<номер\> thread from \<количество\> threads!"

**Пример**:
```
Enter number of threads: 3
I am 0 thread from 3 threads!
I am 1 thread from 3 threads!
I am 2 thread from 3 threads!
```

---

### Задание 4: Скрытая синхронизация
**Файл**: `Task04_SharedPrivate/main.cpp`

Демонстрация работы shared и private переменных в OpenMP, включая race condition при использовании общих переменных.

**Входные данные**: k - количество нитей  
**Выходные данные**: 
- Версия 1: shared переменная без задержки
- Версия 2: shared переменная с задержкой (демонстрация ошибки race condition)
- Версия 3: private переменная (корректная работа)

**Примечание**: Используется функция Sleep(100) для имитации длительных вычислений и демонстрации проблем синхронизации.

---

### Задание 5: Параметр reduction
**Файл**: `Task05_Reduction/main.cpp`

Параллельное вычисление суммы чисел от 1 до N с использованием reduction.

**Входные данные**: 
- N - верхняя граница суммы
- k - количество нитей (для второй версии)

**Выходные данные**: 
- Версия 1: Частичные суммы двух нитей (0: сумма 1..N/2, 1: сумма N/2+1..N)
- Версия 2: Частичные суммы k нитей с динамическим распределением
- Итоговая сумма для каждой версии

**Пример**:
```
Enter N: 4
Version 1 (2 threads with if-else):
[0]: Sum = 3
[1]: Sum = 7
Sum = 10
```

---

### Задание 6: Распараллеливание циклов
**Файл**: `Task06_ForLoop/main.cpp`

Распределение работы по нитям с помощью директивы `#pragma omp for`.

**Входные данные**: 
- k - количество нитей
- N - верхняя граница суммы

**Выходные данные**: 
- Информация о том, какая нить обрабатывает каждую итерацию
- Итоговая сумма чисел от 1 до N

**Пример**:
```
Enter number of threads: 2
Enter N: 4
Processing iterations:
[0]: processing iteration 1
[0]: processing iteration 3
[1]: processing iteration 2
[1]: processing iteration 4
[Final result]:
Sum = 10
```

---

### Задание 7: Параметр schedule
**Файл**: `Task07_Schedule/main.cpp`

Исследование влияния параметра schedule (static, dynamic, guided) на распределение итераций цикла.

**Входные данные**: нет (используется k=4, N=10)  
**Выходные данные**: Таблица распределения итераций по нитям для каждого типа schedule

**Типы schedule**:
- static - равномерное статическое распределение
- static,1 - по 1 итерации на нить
- static,2 - по 2 итерации на нить
- dynamic - динамическое распределение
- dynamic,2 - динамическое по 2 итерации
- guided - адаптивное распределение
- guided,2 - адаптивное с минимумом 2

---

### Задание 8: Число π
**Файл**: `Task08_Pi/main.cpp`

Вычисление числа π методом численного интегрирования по формуле:

π = 4 × Σ(1/(1+x²ᵢ) × 1/N), где xᵢ = (i + 0.5)/N

**Входные данные**: N - точность вычисления (количество итераций)  
**Выходные данные**: Значение π

**Пример**:
```
Enter N (precision): 1000000000
Pi = 3.14159265
```

---

### Задание 9: Умножение матриц
**Файл**: `Task09_Matrix/main.cpp`

Параллельное умножение двух квадратных матриц A × B = C размером n×n.

**Входные данные**: 
- n - размер матриц (1 ≤ n ≤ 10)
- n² элементов матрицы A
- n² элементов матрицы B

**Выходные данные**: n² элементов результирующей матрицы C

**Пример**:
```
Enter matrix size n (1 <= n <= 10): 2
Enter matrix A (2x2):
1 2
3 4
Enter matrix B (2x2):
5 6
7 8

Result matrix C (A x B):
19 22
43 50
```

---

### Задание 10: Параллельные секции
**Файл**: `Task10_Sections/main.cpp`

Использование директив `sections` и `section` для создания параллельных секций кода.

**Входные данные**: k - количество нитей  
**Выходные данные**: 
- k-строк вида "[\<номер\>]: came in section \<номер секции\>"
- k-строк вида "[\<номер\>]: parallel region"

**Пример**:
```
Enter number of threads: 3
[0]: came in section 1
[1]: came in section 2
[2]: came in section 3
[0]: parallel region
[1]: parallel region
[2]: parallel region
```

---

### Задание 11: Гонка потоков - atomic
**Файл**: `Task11_SumAtomic/main.cpp`

Вычисление суммы чисел от 1 до N **без использования reduction**. Вместо этого используется директива `atomic` для безопасного обновления общей переменной.

**Входные данные**: 
- k - количество нитей
- N - верхняя граница суммы

**Выходные данные**: 
- Информация о каждой итерации
- Итоговая сумма

**Примечание**: Директива `#pragma omp atomic` гарантирует атомарность операции, предотвращая race condition при одновременном доступе к переменной sum.

---

### Задание 12: Гонка потоков - critical
**Файл**: `Task12_PiCritical/main.cpp`

Вычисление числа π **без использования reduction**. Используется директива `critical` для синхронизации доступа к общей переменной pi.

**Входные данные**: N - точность вычисления

**Выходные данные**: 
- Частичные суммы каждой нити
- Значение π

**Примечание**: Директива `#pragma omp critical` создает критическую секцию - только одна нить может выполнять код в этой секции одновременно.

---

## Задания MPI (15-32)

### Требования для MPI
Перед запуском MPI программ необходимо:
1. Установить Microsoft MPI Runtime и SDK
2. Программы запускаются через `mpiexec.exe`
3. Для каждого проекта создан файл `run.bat` для удобного запуска

---

### Задание 15: MPI I am!
**Файл**: `Task15_MPI_IAm/main.cpp`

Каждый процесс выводит свой номер и общее количество процессов.

**Запуск**: `mpiexec.exe -np 3 Task15_MPI_IAm.exe`

**Выходные данные**:
```
I am 0 process from 3 processes!
I am 1 process from 3 processes!
I am 2 process from 3 processes!
```

**Функции MPI**:
- `MPI_Init` - инициализация MPI
- `MPI_Comm_rank` - получение номера процесса
- `MPI_Comm_size` - получение количества процессов
- `MPI_Finalize` - завершение MPI

---

### Задание 16: MPI First-Second
**Файл**: `Task16_MPI_FirstSecond/main.cpp`

Процессы с четным номером выводят "SECOND", с нечетным - "FIRST".

**Запуск**: `mpiexec.exe -np 4 Task16_MPI_FirstSecond.exe`

**Выходные данные**:
```
4 processes.
I am 1 process: FIRST!
I am 2 process: SECOND!
I am 3 process: FIRST!
```

---

### Задание 17: MPI Send - блокирующие обмены
**Файл**: `Task17_MPI_Send/main.cpp`

Демонстрация простых блокирующих операций отправки и приема сообщений.

**Запуск**: `mpiexec.exe -np 2 Task17_MPI_Send.exe`

**Выходные данные**:
```
Process 0: sending message '45'
Process 1: receive message '45'
```

**Функции MPI**:
- `MPI_Send` - блокирующая отправка сообщения
- `MPI_Recv` - блокирующий прием сообщения

---

### Задание 18: MPI Эстафетная палочка
**Файл**: `Task18_MPI_Baton/main.cpp`

Последовательная передача сообщения от процесса к процессу по кольцу (0 → 1 → 2 → ... → N-1 → 0).

**Запуск**: `mpiexec.exe -np 4 Task18_MPI_Baton.exe`

**Выходные данные**:
```
[0]: sending message '0'
[1]: receive message '0'
[1]: sending message '1'
[2]: receive message '1'
...
```

**Схема**: Каждый процесс принимает сообщение от предыдущего, увеличивает значение на 1 и отправляет следующему.

---

### Задание 19: MPI Master-Slave
**Файл**: `Task19_MPI_MasterSlave/main.cpp`

Схема "мастер-рабочие": slave-процессы отправляют свои номера master-процессу (процесс 0).

**Запуск**: `mpiexec.exe -np 4 Task19_MPI_MasterSlave.exe`

**Выходные данные**:
```
Master process: waiting for messages from slaves...
Slave process 1: sending message '1' to master
Slave process 2: sending message '2' to master
Slave process 3: sending message '3' to master
Master: receive message '1' from process 1
Master: receive message '2' from process 2
Master: receive message '3' from process 3
```

---

### Задание 20: MPI Isend - неблокирующие обмены
**Файл**: `Task20_MPI_Isend/main.cpp`

Использование неблокирующих операций отправки и приема сообщений.

**Запуск**: `mpiexec.exe -np 2 Task20_MPI_Isend.exe`

**Выходные данные**:
```
Process 0: initiating send of message '45'
Process 1: initiating receive...
Process 0: send initiated, doing other work...
Process 1: receive initiated, doing other work...
Process 0: send completed!
Process 1: receive message '45'
```

**Функции MPI**:
- `MPI_Isend` - неблокирующая отправка (возврат сразу после инициализации)
- `MPI_Irecv` - неблокирующий прием
- `MPI_Wait` - ожидание завершения операции

**Преимущество**: Процесс может выполнять другие вычисления пока идет передача данных.

---

### Задание 21: MPI Ring - кольцевой обмен
**Файл**: `Task21_MPI_Ring/main.cpp`

Каждый процесс отправляет данные следующему и получает от предыдущего по кольцу.

**Запуск**: `mpiexec.exe -np 4 Task21_MPI_Ring.exe`

**Функции MPI**:
- `MPI_Isend` - неблокирующая отправка
- `MPI_Irecv` - неблокирующий прием
- `MPI_Wait` - ожидание завершения операции

---

### Задание 22: MPI All-to-All - полный обмен
**Файл**: `Task22_MPI_AllToAll/main.cpp`

Каждый процесс отправляет сообщения всем другим процессам.

**Запуск**: `mpiexec.exe -np 4 Task22_MPI_AllToAll.exe`

**Функции MPI**:
- `MPI_Isend` - неблокирующая отправка всем
- `MPI_Irecv` - неблокирующий прием от всех
- `MPI_Waitall` - ожидание завершения всех операций

---

### Задание 23: MPI Bcast - широковещательная рассылка
**Файл**: `Task23_MPI_Bcast/main.cpp`

Процесс 0 читает строку и рассылает всем процессам для подсчета вхождений букв.

**Запуск**: `mpiexec.exe -np 4 Task23_MPI_Bcast.exe`

**Входные данные**:
- Длина строки (1 ≤ n ≤ 100)
- Строка для анализа

**Выходные данные**: Количество вхождений каждой буквы алфавита

**Функции MPI**:
- `MPI_Bcast` - широковещательная рассылка данных

---

### Задание 24: MPI Reduce - сбор и редукция данных
**Файл**: `Task24_MPI_Reduce/main.cpp`

Параллельное вычисление числа π с использованием MPI_Reduce для сбора результатов.

**Запуск**: `mpiexec.exe -np 4 Task24_MPI_Reduce.exe`

**Входные данные**: N - точность вычисления

**Выходные данные**: Вычисленное значение π

**Функции MPI**:
- `MPI_Reduce` - редукция (суммирование) данных на одном процессе

---

### Задание 25: MPI Scatter/Gather - распределение и сбор
**Файл**: `Task25_MPI_ScatterGather/main.cpp`

Параллельное умножение матриц с использованием Scatter для распределения строк и Gather для сбора результатов.

**Запуск**: `mpiexec.exe -np 2 Task25_MPI_ScatterGather.exe`

**Входные данные**: n - размер матриц (n² должно делиться на количество процессов)

**Функции MPI**:
- `MPI_Scatter` - распределение данных по процессам
- `MPI_Gather` - сбор данных с процессов

---

### Задание 26: MPI Comm - работа с коммуникаторами
**Файл**: `Task26_MPI_Comm/main.cpp`

Создание нового коммуникатора для подмножества процессов (только четные).

**Запуск**: `mpiexec.exe -np 6 Task26_MPI_Comm.exe`

**Функции MPI**:
- `MPI_Comm_group` - получение группы из коммуникатора
- `MPI_Group_incl` - создание новой группы
- `MPI_Comm_create` - создание коммуникатора

---

### Задание 27: MPI Dynamic - динамическое создание процессов
**Файл**: `Task27_MPI_Dynamic/main.cpp`

Родительский процесс динамически создает дочерние процессы.

**Запуск**: `mpiexec.exe -np 1 Task27_MPI_Dynamic.exe`

**Входные данные**: количество дочерних процессов

**Функции MPI**:
- `MPI_Comm_spawn` - динамическое создание процессов
- `MPI_Comm_get_parent` - проверка родительского процесса

---

### Задание 28: MPI One-Sided - односторонние коммуникации
**Файл**: `Task28_MPI_OneSided/main.cpp`

Вычисление π с использованием односторонних коммуникаций (RMA).

**Запуск**: `mpiexec.exe -np 4 Task28_MPI_OneSided.exe`

**Входные данные**: N - точность вычисления

**Функции MPI**:
- `MPI_Win_create` - создание окна памяти
- `MPI_Put` - односторонняя запись в удаленную память
- `MPI_Win_fence` - синхронизация доступа к окну

---

### Задание 29: MPI Scalability - исследование масштабируемости
**Файл**: `Task29_MPI_Scalability/main.cpp`

Исследование масштабируемости MPI-программ с измерением времени выполнения.

**Запуск**: 
```bash
mpiexec.exe -np 1 Task29_MPI_Scalability.exe
mpiexec.exe -np 2 Task29_MPI_Scalability.exe
mpiexec.exe -np 4 Task29_MPI_Scalability.exe
mpiexec.exe -np 8 Task29_MPI_Scalability.exe
```

**Входные данные**: N - точность вычисления (используйте большое значение, например 1000000000)

**Выходные данные**: 
- Вычисленное значение π
- Время выполнения
- Количество процессов

**Метрики масштабируемости**:
- **Ускорение (Speedup)**: S(p) = T(1) / T(p), где T(1) - время на 1 процессе, T(p) - время на p процессах
- **Эффективность**: E(p) = S(p) / p × 100%
- **Идеальное ускорение**: S(p) = p (линейное ускорение)

**Функции MPI**:
- `MPI_Wtime()` - получение текущего времени с высокой точностью
- `MPI_Barrier()` - синхронизация всех процессов

**Анализ результатов**:
1. Запустите программу с 1, 2, 4, 8 процессами
2. Запишите время выполнения для каждого случая
3. Постройте график зависимости времени от количества процессов
4. Вычислите ускорение и эффективность
5. Сравните с идеальным линейным ускорением

---

### Задание 30: MPI+OpenMP Project - создание проекта с поддержкой MPI и OpenMP
**Файл**: `Task30_MPI_OpenMP_Project/main.cpp`

Учебное задание для настройки проекта с поддержкой как MPI, так и OpenMP.

**Запуск**: `mpiexec.exe -np 2 Task30_MPI_OpenMP_Project.exe`

**Выходные данные**: Сообщения от каждой нити каждого процесса

**Настройка проекта**:
1. **Поддержка OpenMP**: `<OpenMPSupport>true</OpenMPSupport>` в .vcxproj
2. **Поддержка MPI**: 
   - Include: `$(ProjectDir)..\MPI_Include`
   - Library: `C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64`
   - Link: `msmpi.lib`

**Особенность**: Между `MPI_Init` и `MPI_Finalize` создается параллельная область OpenMP, что демонстрирует гибридное программирование

---

### Задание 31: MPI+OpenMP Hybrid - гибридное программирование
**Файл**: `Task31_MPI_OpenMP_IAm/main.cpp`

Комбинация MPI (многопроцессность) и OpenMP (многопоточность).

**Запуск**: `mpiexec.exe -np 2 Task31_MPI_OpenMP_IAm.exe`

**Выходные данные**: Информация о каждой нити из каждого процесса

---

### Задание 32: MPI+OpenMP Pi - гибридное вычисление π
**Файл**: `Task32_MPI_OpenMP_Pi/main.cpp`

Вычисление π с использованием MPI для распределения между процессами и OpenMP для распараллеливания внутри процесса.

**Запуск**: `mpiexec.exe -np 2 Task32_MPI_OpenMP_Pi.exe`

**Входные данные**: N - точность вычисления

**Преимущество**: Двухуровневый параллелизм позволяет эффективно использовать многоядерные кластеры.

---

## Настройка OpenMP в Visual Studio

OpenMP уже включен во всех проектах через настройку `<OpenMPSupport>true</OpenMPSupport>` в файлах .vcxproj.

Если нужно изменить настройки вручную:
1. Правой кнопкой по проекту → **Properties**
2. **C/C++** → **Language** → **Open MP Support** → установить **Yes (/openmp)**

## Настройка MPI в Visual Studio

Для работы с MPI необходимо:

### 1. Установка Microsoft MPI
1. Скачайте и установите [Microsoft MPI](https://www.microsoft.com/en-us/download/details.aspx?id=105289)
2. Установите оба компонента: Runtime и SDK

### 2. Настройка проекта
В файлах .vcxproj уже настроены пути для стандартной установки MPI:
- **Include Directories**: `C:\Program Files (x86)\Microsoft SDKs\MPI\Include`
- **Library Directories**: `C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64`
- **Additional Dependencies**: `msmpi.lib`

> ⚠️ **Если MPI установлен в другую директорию**, см. [SETUP.md](SETUP.md) для инструкций по настройке путей.

### 3. Запуск MPI программ
MPI программы запускаются через `mpiexec.exe`:
```bash
"C:\Program Files\Microsoft MPI\Bin\mpiexec.exe" -np <число_процессов> <путь_к_программе>
```

Для каждого MPI проекта создан файл `run.bat` для упрощенного запуска.

**Пример** (для Task15_MPI_IAm):
```bash
cd Task15_MPI_IAm
run.bat
```

## Управление количеством нитей/процессов

### OpenMP (нити):
1. В коде через `omp_set_num_threads(k)`
2. Через переменную окружения: `set OMP_NUM_THREADS=4`
3. В директиве: `#pragma omp parallel num_threads(k)`

### MPI (процессы):
1. Параметр `-np` при запуске: `mpiexec.exe -np 4 program.exe`
2. Количество процессов определяется при запуске, не в коде

## Примечания

### OpenMP:
- Все программы выполняются в консольном режиме
- Для корректной работы необходима поддержка OpenMP 2.0 или выше
- Порядок вывода из разных нитей может отличаться при разных запусках
- Для измерения производительности используйте Release-сборку

### MPI:
- Каждый процесс выполняется независимо
- Коммуникация между процессами только через сообщения (MPI_Send/MPI_Recv)
- Порядок получения сообщений может варьироваться
- Для отладки используйте небольшое количество процессов (2-4)

## Различия OpenMP и MPI

| Характеристика | OpenMP | MPI |
|---|---|---|
| Модель | Многопоточность (shared memory) | Многопроцессность (distributed memory) |
| Память | Общая для всех нитей | Отдельная для каждого процесса |
| Коммуникация | Через общие переменные | Через передачу сообщений |
| Запуск | Автоматическое создание нитей | Запуск через mpiexec |
| Масштабируемость | До количества ядер процессора | До количества узлов кластера |
| Применение | Однопроцессорные системы | Кластеры, суперкомпьютеры |

## Структура репозитория

```
📦 Parallel and Multithreaded Programming
├── 📄 README.md                    # Основная документация
├── 📄 SETUP.md                     # Инструкции по установке и настройке
├── 📄 INSTALL_MPI.md               # Детальная установка MPI
├── 📄 MPI_TROUBLESHOOTING.md       # Решение проблем с MPI
├── 📄 TASKS_COMPLETED.md           # Список выполненных заданий
├── 📄 LICENSE                      # Лицензия MIT
├── 📄 .gitignore                   # Игнорируемые файлы
├── 📄 OpenMP_Labs.sln              # Solution Visual Studio
├── 📁 MPI_Include/                 # Заголовочные файлы MPI
├── 📁 Task02_HelloWorld/           # Задания OpenMP (02-12)
├── 📁 Task15_MPI_IAm/              # Задания MPI (15-28)
├── 📁 Task29_MPI_Scalability/      # Задания масштабируемости (29)
├── 📁 Task30_MPI_OpenMP_Project/   # Гибридные задания (30-32)
└── 📁 Task31_MPI_OpenMP_IAm/
```

## Автор

Лабораторные работы по курсу "Параллельное и многопоточное программирование"

## Лицензия

MIT License - см. файл [LICENSE](LICENSE)

Учебный проект для изучения параллельного программирования с использованием OpenMP и MPI.

## Благодарности

- Microsoft MPI за библиотеку MPI для Windows
- Сообщество OpenMP за стандарт параллельного программирования

---

⭐ Если этот проект был полезен, поставьте звезду на GitHub!

