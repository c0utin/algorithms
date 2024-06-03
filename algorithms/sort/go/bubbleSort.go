package main

import (
	"fmt"
)

func bubbleSort(arr []int) []int {
    n := len(arr)
    for i := 0; i < n; i++ {
        for j := 0; j < n-i-1; j++ {
            if arr[j] > arr[j+1] {
                arr[j], arr[j+1] = arr[j+1], arr[j]
            }
        }
    }
    return arr
}

func main() {

	arr :=  []int{1,6,3,5,9}
	sortedArr := bubbleSort(arr)
	fmt.Printf("sorted arr: %v\n", sortedArr)
}

