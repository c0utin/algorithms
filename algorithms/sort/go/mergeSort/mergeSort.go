package main

import (
    "fmt"
    "sync"
)

func merge(left, right []int) []int {
    result := make([]int, 0, len(left)+len(right))
    i, j := 0, 0

    for i < len(left) && j < len(right) {
        if left[i] < right[j] {
            result = append(result, left[i])
            i++
        } else {
            result = append(result, right[j])
            j++
        }
    }

    result = append(result, left[i:]...)
    result = append(result, right[j:]...)

    return result
}

func mergeSort(arr []int) []int {
    if len(arr) <= 1 {
        return arr
    }

    mid := len(arr) / 2

    var left, right []int

    var wg sync.WaitGroup
    wg.Add(2)

    // Sort the left half concurrently
    go func() {
        defer wg.Done()
        left = mergeSort(arr[:mid])
    }()

    // Sort the right half concurrently
    go func() {
        defer wg.Done()
        right = mergeSort(arr[mid:])
    }()

    wg.Wait() // Wait for both goroutines to finish

    return merge(left, right)
}

func main() {
    arr := []int{1, 6, 3, 5, 9}
    sortedArr := mergeSort(arr)
    fmt.Printf("Sorted arr: %v\n", sortedArr)
}

