# Скрипт очистки проекта перед публикацией на GitHub
# Запустите в PowerShell: .\clean-for-github.ps1

Write-Host "======================================" -ForegroundColor Cyan
Write-Host "Очистка проекта перед публикацией на GitHub" -ForegroundColor Cyan
Write-Host "======================================" -ForegroundColor Cyan
Write-Host ""

# Функция для безопасного удаления
function Remove-SafelyItem {
    param($Path, $Description)
    
    if (Test-Path $Path) {
        try {
            Remove-Item -Path $Path -Recurse -Force -ErrorAction Stop
            Write-Host "[✓] Удалено: $Description" -ForegroundColor Green
        }
        catch {
            Write-Host "[✗] Ошибка при удалении $Description`: $_" -ForegroundColor Red
        }
    }
    else {
        Write-Host "[~] Не найдено: $Description" -ForegroundColor Yellow
    }
}

Write-Host "1. Удаление больших файлов..." -ForegroundColor White
Remove-SafelyItem "msmpisdk.msi" "Установщик MPI (99MB)"
Remove-SafelyItem "method.docx" "Методичка (авторские права)"

Write-Host ""
Write-Host "2. Удаление скомпилированных файлов..." -ForegroundColor White
Remove-SafelyItem "x64" "Скомпилированные бинарники"

Write-Host ""
Write-Host "3. Удаление личных настроек Visual Studio..." -ForegroundColor White
Get-ChildItem -Recurse -Filter "*.user" -ErrorAction SilentlyContinue | ForEach-Object {
    Remove-Item $_.FullName -Force
    Write-Host "[✓] Удален: $($_.Name)" -ForegroundColor Green
}

Write-Host ""
Write-Host "4. Удаление папок Debug внутри проектов..." -ForegroundColor White
Get-ChildItem -Recurse -Directory -Filter "Debug" -ErrorAction SilentlyContinue | ForEach-Object {
    Remove-SafelyItem $_.FullName "Debug: $($_.Parent.Name)"
}

Write-Host ""
Write-Host "5. Проверка размера проекта..." -ForegroundColor White
$totalSize = (Get-ChildItem -Recurse -File | Measure-Object -Property Length -Sum).Sum / 1MB
Write-Host "Общий размер проекта: $([math]::Round($totalSize, 2)) MB" -ForegroundColor Cyan

if ($totalSize -gt 10) {
    Write-Host "[!] ПРЕДУПРЕЖДЕНИЕ: Размер больше 10 MB!" -ForegroundColor Red
    Write-Host "    Проверьте наличие больших файлов:" -ForegroundColor Yellow
    Get-ChildItem -Recurse -File | Where-Object { $_.Length -gt 1MB } | 
        Select-Object Name, @{Name="Size(MB)";Expression={[math]::Round($_.Length/1MB,2)}}, FullName |
        Format-Table -AutoSize
}
else {
    Write-Host "[✓] Размер проекта в норме для GitHub" -ForegroundColor Green
}

Write-Host ""
Write-Host "6. Создание списка файлов для коммита..." -ForegroundColor White
$fileList = git ls-files 2>$null
if ($LASTEXITCODE -eq 0) {
    Write-Host "[✓] Git уже инициализирован" -ForegroundColor Green
    Write-Host "    Количество отслеживаемых файлов: $($fileList.Count)" -ForegroundColor Cyan
}
else {
    Write-Host "[~] Git еще не инициализирован" -ForegroundColor Yellow
    Write-Host "    Запустите: git init" -ForegroundColor Cyan
}

Write-Host ""
Write-Host "======================================" -ForegroundColor Cyan
Write-Host "Очистка завершена!" -ForegroundColor Green
Write-Host "======================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "Следующие шаги:" -ForegroundColor Yellow
Write-Host "1. Проверьте файлы: git status" -ForegroundColor White
Write-Host "2. Добавьте файлы: git add ." -ForegroundColor White
Write-Host "3. Создайте коммит: git commit -m 'Initial commit'" -ForegroundColor White
Write-Host "4. Свяжите с GitHub: git remote add origin <URL>" -ForegroundColor White
Write-Host "5. Загрузите: git push -u origin main" -ForegroundColor White
Write-Host ""
Write-Host "Подробнее см. файл .github-checklist.md" -ForegroundColor Cyan
Write-Host ""

