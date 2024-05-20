#include <stdio.h>

#define TRUE 1
#define FALSE 0

void binarySearch(int *arr, int target, int lo, int hi){
	
	while(hi >= lo){

		int m = lo + (hi - lo) / 2;
		int v = arr[m];

		if  (v == target) {
			printf("%d\n", TRUE);
			return;
		}
		else if (v < target) {
			lo = m + 1;
		}
		else{
			hi = m - 1;
		}
	}	
	printf("%d\n", FALSE);
}

int main() {


	// sorted array
	int arr[] = {1,2,3,4,5,6,7,8,9,69};
	int lower = 0;
	int high = (sizeof(arr) / sizeof(arr[0]) -1);
	binarySearch(arr, 69, lower, high);

	return 0;
}

