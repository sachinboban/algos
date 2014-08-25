/*
 * Insertion sort
 * Suitable to run for a small number of elements
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
 * Documentation
 * ----------------------------------------------------------------------------
 * Input: A[1...n]
 * 
 * Working: At any iteration i, A[1...i-1] are sorted. Find the relative 
 * position of A[i] wrt to the sorted array A[1...i-1]. Perform any right shift
 * if required.
 *
 * Complexity: O(n^2) [worst case]
 */
int insertion_sort(int *array, int size);

int main()
{

	int *array = NULL;
	int index, size = 0;
	
	scanf("%d", &size);

	array = malloc(sizeof(int) * size);
	if(array) {
		printf("ERROR: malloc()\n");
		return 0;
	}
	memset(array, 0, sizeof(int) * size);
	
	for(index = 0; index < size; index++) {
		scanf("%d", &array[index]);
	}

	insertion_sort(array, size);
	for(index = 0; index < size; index++) {
		printf("%d ", array[index]);
	}

	free(array);
	return 0;
}

int insertion_sort(int *array, int size)
{
	int index, swap_position, swap_data;
	for(index = 1; index < size; index++) {
		if (array[index] < array[index - 1]) {
			swap_position = index - 1;
			swap_data = array[index];
			
			while(swap_position >= 0 && swap_data < array[swap_position]) {
				array[swap_position + 1] = array[swap_position];
				swap_position -= 1;
			}
			array[swap_position] = swap_data;
		}
	}

	return 0;
}
