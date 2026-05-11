# Инструкция по установке и настройке Microsoft MPI

Лабораторные на **Go** (`TaskGo_Lab/`) MPI не требуют; для них см. [SETUP.md](SETUP.md) и раздел Go в [README.md](README.md).

## Шаг 1: Загрузка Microsoft MPI

1. Перейдите на официальную страницу Microsoft MPI:
   https://www.microsoft.com/en-us/download/details.aspx?id=105289

2. Скачайте оба компонента:
   - **msmpisetup.exe** (Microsoft MPI Runtime)
   - **msmpisdk.msi** (Microsoft MPI SDK)

## Шаг 2: Установка

### 2.1 Установка Runtime
1. Запустите **msmpisetup.exe**
2. Следуйте инструкциям мастера установки
3. Установка по умолчанию в: `C:\Program Files\Microsoft MPI\`

### 2.2 Установка SDK
1. Запустите **msmpisdk.msi**
2. Следуйте инструкциям мастера установки
3. SDK устанавливается в ту же папку

## Шаг 3: Проверка установки

Откройте командную строку (cmd) и выполните:
```cmd
mpiexec -help
```

Если команда выполнилась успешно - MPI установлен корректно.

## Шаг 4: Настройка переменных окружения (опционально)

Если `mpiexec` не найден, добавьте в PATH:
1. Откройте "Система" → "Дополнительные параметры системы"
2. Нажмите "Переменные среды"
3. В "Системные переменные" найдите "Path"
4. Добавьте: `C:\Program Files\Microsoft MPI\Bin`

## Шаг 5: Сборка проектов в Visual Studio

1. Откройте `OpenMP_Labs.sln` в Visual Studio
2. Выберите конфигурацию **Debug** или **Release**
3. Выберите платформу **x64**
4. Соберите solution (Build → Build Solution или F7)

## Шаг 6: Запуск MPI программ

### Способ 1: Через bat-файлы
Для каждого MPI проекта создан файл `run.bat`:
```cmd
cd Task15_MPI_IAm
run.bat
```

### Способ 2: Вручную через командную строку
```cmd
cd x64\Debug
"C:\Program Files\Microsoft MPI\Bin\mpiexec.exe" -np 4 Task15_MPI_IAm.exe
```

Где:
- `-np 4` - количество процессов (измените на нужное)
- `Task15_MPI_IAm.exe` - имя программы

## Распространенные проблемы

### Проблема 1: mpiexec не найден
**Решение**: Добавьте путь к MPI в PATH (см. Шаг 4)

### Проблема 2: Ошибка при линковке (msmpi.lib not found)
**Решение**: 
1. Убедитесь, что установлен MPI SDK
2. Проверьте пути в свойствах проекта:
   - Include: `C:\Program Files\Microsoft MPI\Inc`
   - Library: `C:\Program Files\Microsoft MPI\Lib\x64`

### Проблема 3: Программа не запускается
**Решение**:
1. Убедитесь, что установлен MPI Runtime
2. Проверьте, что программа собрана для x64
3. Запускайте через `mpiexec`, а не напрямую

## Тестирование установки

Запустите простой тест:
```cmd
cd x64\Debug
"C:\Program Files\Microsoft MPI\Bin\mpiexec.exe" -np 2 Task15_MPI_IAm.exe
```

Ожидаемый результат:
```
I am 0 process from 2 processes!
I am 1 process from 2 processes!
```

## Дополнительные ресурсы

- [Документация Microsoft MPI](https://docs.microsoft.com/en-us/message-passing-interface/microsoft-mpi)
- [MPI Tutorial](https://mpitutorial.com/)
- [MPI Standard](https://www.mpi-forum.org/)

## Версии

- **Microsoft MPI**: v10.1.2 или новее
- **Visual Studio**: 2019 или новее
- **Windows**: 10 или выше

