# Настройка проекта

## Требования

- **Visual Studio 2019** или новее с поддержкой C++14
- **Microsoft MPI** (MS-MPI)
- **Windows 10** или выше

## Установка Microsoft MPI

### Вариант 1: Через официальный сайт
1. Скачайте [Microsoft MPI](https://www.microsoft.com/en-us/download/details.aspx?id=105289)
2. Установите оба компонента:
   - `msmpisetup.exe` (Runtime)
   - `msmpisdk.msi` (SDK)

### Вариант 2: Через Chocolatey
```powershell
choco install microsoft-mpi
```

## Настройка путей к MPI

После установки MPI проверьте пути в файлах `.vcxproj`:

### Если MPI установлен в стандартную директорию:
- Include: `C:\Program Files (x86)\Microsoft SDKs\MPI\Include`
- Library: `C:\Program Files (x86)\Microsoft SDKs\MPI\Lib\x64`

Пути уже настроены в проектах. Если MPI установлен в другую директорию:

1. Откройте проект в Visual Studio
2. Правой кнопкой → **Properties**
3. **C/C++** → **General** → **Additional Include Directories**
   - Измените путь на ваш путь к `MPI\Include`
4. **Linker** → **General** → **Additional Library Directories**
   - Измените путь на ваш путь к `MPI\Lib\x64`

### Альтернатива: использование переменных окружения

MPI устанавливает переменные окружения:
- `MSMPI_INC` - путь к Include
- `MSMPI_LIB64` - путь к библиотекам x64

Вы можете изменить пути в `.vcxproj` файлах:
```xml
<AdditionalIncludeDirectories>$(MSMPI_INC);%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
<AdditionalLibraryDirectories>$(MSMPI_LIB64);%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>
```

## Компиляция

### Через Visual Studio:
1. Откройте `OpenMP_Labs.sln`
2. Выберите конфигурацию **Debug** и платформу **x64**
3. Выберите нужный проект в Solution Explorer
4. Нажмите **F7** для сборки или **Ctrl+F5** для запуска

### Через командную строку:
```powershell
msbuild OpenMP_Labs.sln /p:Configuration=Debug /p:Platform=x64
```

## Запуск MPI программ

### Базовый запуск:
```powershell
mpiexec -np 4 x64\Debug\Task15_MPI_IAm.exe
```

### Через bat-файлы:
В каждой MPI-папке есть `run.bat`:
```powershell
cd Task15_MPI_IAm
run.bat
```

## Проверка установки MPI

```powershell
# Проверка версии
mpiexec -help

# Проверка переменных окружения
echo %MSMPI_INC%
echo %MSMPI_LIB64%
```

## Go (лабораторные `TaskGo_Lab/`)

Для программ на Go нужен компилятор **Go 1.22+** ([скачать](https://go.dev/dl/)).

### Windows
Установите официальный MSI с `go.dev`, затем в новом терминале:

```powershell
go version
```

### macOS (Homebrew)

```bash
brew install go
eval "$(/opt/homebrew/bin/brew shellenv)"   # при необходимости добавить brew в PATH
go version
```

### Запуск лаб из репозитория

Из **корня** (файл `go.work` подключает `./TaskGo_Lab`):

```bash
go run ./TaskGo_Lab/hello
```

Из каталога модуля:

```bash
cd TaskGo_Lab
go run ./hello
```

Подробнее — [README.md](README.md), раздел «Go: сборка и запуск».

## Решение проблем

См. файл [MPI_TROUBLESHOOTING.md](MPI_TROUBLESHOOTING.md) для решения типичных проблем.

