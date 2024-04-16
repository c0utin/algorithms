#include <stdio.h>
#include <stdlib.h>

int main()
{

	int* ptr;
	int size = 5;


	ptr = (int*)calloc(size, sizeof(int));

	if (ptr == NULL) {
		printf("Memory not allocated.\n");
		exit(0);
	}
	else {
		printf("Memory successfully allocated using "
			"calloc.\n");
	}

	for (int j = 0; j < size; ++j) {
		ptr[j] = j + 1;
	}

	printf("The elements of the array are: ");
	for (int k = 0; k < size; ++k) {
		printf("%d, ", ptr[k]);
	}

	printf("\n");

  printf("New size of dynamic array\n");
  scanf("%d", &size);

	int *temp = ptr;

	ptr = realloc(ptr, size * sizeof(int));
	if (!ptr) {
		printf("Memory Re-allocation failed.");
		ptr = temp;
	}
	else {
		printf("Memory successfully re-allocated using "
			"realloc.\n");
	}

	for (int j = 5; j < size; ++j) {
		ptr[j] = j + 10;
	}

	printf("The new elements of the array are: ");
	for (int k = 0; k < size; ++k) {
		printf("%d, ", ptr[k]);
	}
	return 0;
}
