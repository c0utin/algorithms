#include <stdio.h>

#define TRUE 1
#define FALSE 0

int linearSearch(int *arr, int size, int target){

  for(int i = 0; i < size; i++){
    if (arr[i] == target){
      return TRUE;
    }
  }
  return FALSE;
}

int main(){

  int arr[] = {2,6,9,69};

  if(linearSearch(arr, 4, 69)) {
    printf("LOL\n");
  } else {
    printf("KEKW\n");
  }
}
