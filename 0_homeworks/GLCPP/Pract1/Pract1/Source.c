#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <time.h>

void bubble_sort(int *arr, int n) {
	// can be implemented in more efficient way
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < n - i - 1; k++) {
			if (arr[i] < arr[k]) {
				// swap
				int tmp = arr[i];
				arr[i] = arr[k];
				arr[k] = tmp;
			}
		}
	}
}

void generate_data(int *arr, int n) {
	srand(time(0));
	for (int i = 0; i < n; i++) {
		arr[i] = rand() % 100 + 1;
	}
}

void print_data(int *arr, int n) {
	printf("\n\nPrinting data...\n");

	for (int i = 0; i < n; i++) {
		printf("\tCell %d: %d\n", i, arr[i]);
	}
}

int main(void) {
	int n = 20'000'000;
	int *arr = malloc(sizeof(int) * n);

	generate_data(arr, n);
	//print_data(arr, n);

	bubble_sort(arr, n);
	//print_data(arr, n);

	// mem leakage
	free(arr); 

	system("pause");
	return 0;
}