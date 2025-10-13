# Скрипт для загрузки проекта в GitHub
# Репозиторий: https://github.com/parasha3a/Parallel-programming-laboratory-work.git

Write-Host "======================================" -ForegroundColor Cyan
Write-Host "Загрузка проекта в GitHub" -ForegroundColor Cyan
Write-Host "======================================" -ForegroundColor Cyan
Write-Host ""

# Шаг 1: Очистка проекта
Write-Host "Шаг 1: Очистка проекта от лишних файлов..." -ForegroundColor Yellow
Write-Host ""

if (Test-Path ".\clean-for-github.ps1") {
    & .\clean-for-github.ps1
} else {
    Write-Host "[!] Файл clean-for-github.ps1 не найден. Очистка вручную..." -ForegroundColor Yellow
    
    # Удаление больших файлов
    if (Test-Path "msmpisdk.msi") { Remove-Item "msmpisdk.msi" -Force; Write-Host "[✓] Удален msmpisdk.msi" -ForegroundColor Green }
    if (Test-Path "method.docx") { Remove-Item "method.docx" -Force; Write-Host "[✓] Удален method.docx" -ForegroundColor Green }
    if (Test-Path "x64") { Remove-Item "x64" -Recurse -Force; Write-Host "[✓] Удалена папка x64" -ForegroundColor Green }
    
    # Удаление .user файлов
    Get-ChildItem -Recurse -Filter "*.user" -ErrorAction SilentlyContinue | ForEach-Object {
        Remove-Item $_.FullName -Force
        Write-Host "[✓] Удален: $($_.Name)" -ForegroundColor Green
    }
}

Write-Host ""
Write-Host "======================================" -ForegroundColor Cyan

# Шаг 2: Проверка Git
Write-Host "Шаг 2: Проверка Git..." -ForegroundColor Yellow
Write-Host ""

$gitInstalled = Get-Command git -ErrorAction SilentlyContinue
if (-not $gitInstalled) {
    Write-Host "[✗] Git не установлен!" -ForegroundColor Red
    Write-Host "    Установите Git: https://git-scm.com/download/win" -ForegroundColor Yellow
    exit 1
}

Write-Host "[✓] Git установлен: $(git --version)" -ForegroundColor Green
Write-Host ""

# Шаг 3: Инициализация репозитория
Write-Host "Шаг 3: Инициализация Git репозитория..." -ForegroundColor Yellow
Write-Host ""

if (Test-Path ".git") {
    Write-Host "[~] Git репозиторий уже инициализирован" -ForegroundColor Yellow
} else {
    git init
    Write-Host "[✓] Git репозиторий инициализирован" -ForegroundColor Green
}

# Проверка текущей ветки
$currentBranch = git branch --show-current 2>$null
if ($currentBranch -ne "main") {
    git branch -M main
    Write-Host "[✓] Переименована ветка в 'main'" -ForegroundColor Green
}

Write-Host ""

# Шаг 4: Добавление файлов
Write-Host "Шаг 4: Добавление файлов в Git..." -ForegroundColor Yellow
Write-Host ""

git add .
$filesAdded = (git diff --cached --numstat | Measure-Object).Count

if ($filesAdded -eq 0) {
    Write-Host "[!] Нет файлов для добавления" -ForegroundColor Red
    Write-Host "    Возможно, все файлы уже закоммичены" -ForegroundColor Yellow
} else {
    Write-Host "[✓] Добавлено файлов: $filesAdded" -ForegroundColor Green
}

Write-Host ""
Write-Host "Список файлов для коммита:" -ForegroundColor Cyan
git status --short
Write-Host ""

# Шаг 5: Создание коммита
Write-Host "Шаг 5: Создание коммита..." -ForegroundColor Yellow
Write-Host ""

$commitMessage = "Initial commit: OpenMP and MPI parallel programming labs

- 32 лабораторные работы по параллельному программированию
- OpenMP задания (Task02-Task12): многопоточность
- MPI задания (Task15-Task28): распределенные вычисления
- Гибридные MPI+OpenMP (Task30-Task32)
- Полная документация и инструкции по установке"

git commit -m $commitMessage

if ($LASTEXITCODE -eq 0) {
    Write-Host "[✓] Коммит создан успешно" -ForegroundColor Green
} else {
    Write-Host "[✗] Ошибка при создании коммита" -ForegroundColor Red
    Write-Host "    Возможно, нет изменений для коммита" -ForegroundColor Yellow
}

Write-Host ""

# Шаг 6: Подключение к GitHub
Write-Host "Шаг 6: Подключение к GitHub репозиторию..." -ForegroundColor Yellow
Write-Host ""

$remoteUrl = "https://github.com/parasha3a/Parallel-programming-laboratory-work.git"
$existingRemote = git remote get-url origin 2>$null

if ($existingRemote) {
    if ($existingRemote -eq $remoteUrl) {
        Write-Host "[~] Remote 'origin' уже настроен на $remoteUrl" -ForegroundColor Yellow
    } else {
        Write-Host "[!] Remote 'origin' указывает на другой репозиторий: $existingRemote" -ForegroundColor Yellow
        Write-Host "    Обновляю на $remoteUrl" -ForegroundColor Cyan
        git remote set-url origin $remoteUrl
    }
} else {
    git remote add origin $remoteUrl
    Write-Host "[✓] Remote 'origin' добавлен: $remoteUrl" -ForegroundColor Green
}

Write-Host ""

# Шаг 7: Загрузка на GitHub
Write-Host "Шаг 7: Загрузка на GitHub..." -ForegroundColor Yellow
Write-Host ""
Write-Host "Выполняю: git push -u origin main" -ForegroundColor Cyan
Write-Host ""

git push -u origin main

if ($LASTEXITCODE -eq 0) {
    Write-Host ""
    Write-Host "======================================" -ForegroundColor Green
    Write-Host "✓ УСПЕШНО ЗАГРУЖЕНО НА GITHUB!" -ForegroundColor Green
    Write-Host "======================================" -ForegroundColor Green
    Write-Host ""
    Write-Host "Репозиторий: https://github.com/parasha3a/Parallel-programming-laboratory-work" -ForegroundColor Cyan
    Write-Host ""
    Write-Host "Следующие шаги:" -ForegroundColor Yellow
    Write-Host "1. Откройте репозиторий в браузере" -ForegroundColor White
    Write-Host "2. Проверьте, что все файлы загружены" -ForegroundColor White
    Write-Host "3. Отредактируйте README.md при необходимости" -ForegroundColor White
    Write-Host "4. Добавьте темы (topics) в настройках репозитория:" -ForegroundColor White
    Write-Host "   - parallel-programming" -ForegroundColor Gray
    Write-Host "   - openmp" -ForegroundColor Gray
    Write-Host "   - mpi" -ForegroundColor Gray
    Write-Host "   - cpp" -ForegroundColor Gray
    Write-Host "   - visual-studio" -ForegroundColor Gray
    Write-Host ""
} else {
    Write-Host ""
    Write-Host "======================================" -ForegroundColor Red
    Write-Host "✗ ОШИБКА ПРИ ЗАГРУЗКЕ" -ForegroundColor Red
    Write-Host "======================================" -ForegroundColor Red
    Write-Host ""
    Write-Host "Возможные причины:" -ForegroundColor Yellow
    Write-Host "1. Нет прав доступа к репозиторию" -ForegroundColor White
    Write-Host "2. Не настроена аутентификация Git" -ForegroundColor White
    Write-Host "3. Проблемы с сетью" -ForegroundColor White
    Write-Host ""
    Write-Host "Решение:" -ForegroundColor Cyan
    Write-Host "1. Настройте Git credentials:" -ForegroundColor White
    Write-Host "   git config --global user.name 'Your Name'" -ForegroundColor Gray
    Write-Host "   git config --global user.email 'your.email@example.com'" -ForegroundColor Gray
    Write-Host ""
    Write-Host "2. Настройте аутентификацию через Personal Access Token:" -ForegroundColor White
    Write-Host "   https://github.com/settings/tokens" -ForegroundColor Gray
    Write-Host ""
    Write-Host "3. Или используйте SSH:" -ForegroundColor White
    Write-Host "   git remote set-url origin git@github.com:parasha3a/Parallel-programming-laboratory-work.git" -ForegroundColor Gray
    Write-Host ""
}

Write-Host ""
Write-Host "Нажмите любую клавишу для выхода..." -ForegroundColor Gray
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")

