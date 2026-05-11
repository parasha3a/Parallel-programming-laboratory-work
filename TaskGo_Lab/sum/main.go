package main

import (
	"fmt"
	"runtime"
	"sync"
	"sync/atomic"
)

// parallelSum делит values на до workers отрезков, в каждом считает локальную сумму,
// добавляет её в общий счётчик через atomic (итог эквивалентен последовательной сумме).
func parallelSum(values []int64, workers int) int64 {
	n := len(values)
	if n == 0 {
		return 0
	}
	if workers < 1 {
		workers = 1
	}
	// Воркеров не больше, чем элементов: иначе часть горутин получила бы пустой диапазон.
	if workers > n {
		workers = n
	}

	// Округление вверх: каждый воркер обрабатывает примерно chunk элементов (последний кусок может быть короче).
	chunk := (n + workers - 1) / workers
	var wg sync.WaitGroup
	var total atomic.Int64 // общий результат; Add и Load потокобезопасны

	for w := 0; w < workers; w++ {
		start := w * chunk
		end := start + chunk
		if end > n {
			end = n
		}
		if start >= end {
			// для данного индекса w диапазон пуст — горутину не запускаем
			break
		}
		wg.Add(1)
		go func(lo, hi int) {
			defer wg.Done()
			var part int64
			for _, v := range values[lo:hi] {
				part += v
			}
			total.Add(part) // атомарное += к общей сумме
		}(start, end)
	}
	wg.Wait()
	return total.Load()
}

func main() {
	runtime.GOMAXPROCS(runtime.NumCPU())

	// Тестовые данные: миллион единиц — ожидаемая сумма ровно size (проверка корректности).
	const size = 1_000_000
	values := make([]int64, size)
	for i := range values {
		values[i] = 1
	}
	workers := runtime.GOMAXPROCS(0) // сколько потоков ОС выделено (обычно = NumCPU)
	got := parallelSum(values, workers)
	fmt.Printf("сумма %d единиц = %d (воркеров: %d, atomic reduction)\n", size, got, workers)
}
