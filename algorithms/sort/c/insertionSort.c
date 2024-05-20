#include <stdio.h>

void Print(int arr[], int size){

   for(int i = 0; i < size; i++){
       printf("%d ", arr[i]);
   }
   printf("\n");
}

void InsertionSort(int arr[], int size){

    for(int i = 1; i < size; i++){
        int key = arr[i];
        int j = i - 1;

        while(j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int arr[] = {3, 8, 2, 5, 10};
    int size = sizeof(arr) / sizeof(arr[0]);

    Print(arr, size);
    InsertionSort(arr, size);
    Print(arr, size);

    return 0;
}
