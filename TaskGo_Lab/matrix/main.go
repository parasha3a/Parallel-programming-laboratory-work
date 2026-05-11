package main

import (
	"fmt"
	"runtime"
	"strings"
	"sync"
)

// printMatrix выводит все элементы матрицы построчно: m[i][j] для каждой ячейки.
func printMatrix(title string, m [][]int) {
	fmt.Println(title)
	if len(m) == 0 {
		fmt.Println("  (пусто)")
		return
	}
	for i := range m {
		var b strings.Builder
		for j := range m[i] {
			if j > 0 {
				b.WriteString("\t")
			}
			fmt.Fprintf(&b, "%d", m[i][j])
		}
		fmt.Println(b.String())
	}
}

// multiplyParallel заполняет матрицу C размера rows×cols (здесь cols = len(b[0])).
// Параметр workers — число горутин; строки i распределяются по кругу между ними.
func multiplyParallel(a, b [][]int, workers int) [][]int {
	rows := len(a)       // число строк A и строк C
	cols := len(b[0])    // число столбцов B и столбцов C
	inner := len(b)      // число строк B = число столбцов A (согласованность умножения)
	if len(a) == 0 || len(a[0]) != inner {
		panic("размеры A и B несовместимы: нужно len(A[0]) == len(B)")
	}

	c := make([][]int, rows)
	for i := range c {
		c[i] = make([]int, cols)
	}
	if workers < 1 {
		workers = 1
	}

	var wg sync.WaitGroup
	for w := 0; w < workers; w++ {
		wg.Add(1)
		go func(rank int) {
			defer wg.Done()
			// Строки с шагом workers: у каждой горутины свой «сдвиг» rank (0..workers-1).
			for i := rank; i < rows; i += workers {
				for j := 0; j < cols; j++ {
					s := 0
					// Стандартное скалярное произведение i-й строки A на j-й столбец B
					for k := 0; k < inner; k++ {
						s += a[i][k] * b[k][j]
					}
					c[i][j] = s
				}
			}
		}(w)
	}
	wg.Wait()
	return c
}

func main() {
	runtime.GOMAXPROCS(runtime.NumCPU())

	var rows, cols int
	fmt.Print("Число строк матрицы A: ")
	if _, err := fmt.Scan(&rows); err != nil || rows < 1 {
		fmt.Println("некорректное число строк")
		return
	}
	fmt.Print("Число столбцов матрицы A (и строк B): ")
	if _, err := fmt.Scan(&cols); err != nil || cols < 1 {
		fmt.Println("некорректное число столбцов")
		return
	}

	// A: rows×cols; B: cols×rows — тогда C = A*B имеет размер rows×rows.
	a := make([][]int, rows)
	b := make([][]int, cols)
	for i := 0; i < rows; i++ {
		a[i] = make([]int, cols)
		for j := 0; j < cols; j++ {
			a[i][j] = (i + j) % 7
		}
	}
	for i := 0; i < cols; i++ {
		b[i] = make([]int, rows)
		for j := 0; j < rows; j++ {
			b[i][j] = (i - j + rows) % 5
		}
	}

	workers := runtime.GOMAXPROCS(0)
	c := multiplyParallel(a, b, workers)
	outCols := len(c[0])

	fmt.Printf("Размеры: A %d×%d, B %d×%d → C %d×%d (воркеров=%d)\n\n",
		rows, cols, cols, rows, rows, outCols, workers)

	printMatrix("Матрица A (все ячейки):", a)
	fmt.Println()
	printMatrix("Матрица B (все ячейки):", b)
	fmt.Println()
	printMatrix("Матрица C = A·B (все ячейки):", c)
}
