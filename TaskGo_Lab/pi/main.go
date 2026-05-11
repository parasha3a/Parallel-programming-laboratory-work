package main

import (
	"fmt"
	"runtime"
	"sync"
)

func main() {
	runtime.GOMAXPROCS(runtime.NumCPU())

	var N int64
	fmt.Print("Enter N (precision): ")
	if _, err := fmt.Scan(&N); err != nil {
		N = 2
	}
	if N < 2 {
		N = 2
	}
	if N%2 != 0 {
		N++ // Симпсон требует чётного числа подотрезков
	}

	h := 1.0 / float64(N)
	workers := runtime.GOMAXPROCS(0)
	if workers < 1 {
		workers = 1
	}

	// Буфер ёмкости workers: каждая горутина один раз отправляет свою частичную сумму без взаимной блокировки.
	partials := make(chan float64, workers)
	var wg sync.WaitGroup

	for w := 0; w < workers; w++ {
		wg.Add(1)
		go func(rank int) {
			defer wg.Done()
			var local float64
			for j := int64(rank); j <= N; j += int64(workers) {
				x := h * float64(j)
				f := 4.0 / (1.0 + x*x)
				var weight float64
				switch {
				case j == 0 || j == N:
					weight = 1.0
				case j%2 == 1:
					weight = 4.0
				default:
					weight = 2.0
				}
				local += weight * f
			}
			partials <- local
		}(w)
	}
	// Закрываем канал только после завершения всех отправителей — иначе range зависнет или паника.
	go func() {
		wg.Wait()
		close(partials)
	}()

	var total float64
	for p := range partials {
		total += p
	}
	pi := (h / 3.0) * total
	fmt.Printf("Calculated PI = %.8f (Simpson, N=%d subintervals, workers=%d, chan gather)\n", pi, N, workers)
}
