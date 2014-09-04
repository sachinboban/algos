/*
 * Insertion sort
 * Suitable to run for a small number of elements
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
 * Solution
 * ----------------------------------------------------------------------------
 * Input: A[1...n]
 * 
 * Working: At any iteration i, A[1...i-1] are sorted. Find the relative 
 * position of A[i] wrt to the sorted array A[1...i-1]. Perform any right shift
 * if required.
 *
 * Complexity: O(n^2) [worst case]
 */

/*
 * insertion_sort
 * @array		array of elements to be sorted
 * @size		size of the array to be sorted
 *
 * Sorts the array using insertion sort. At any iteration i, A[0...i-1] is
 * is sorted. We compare A[i] with A[i-1,..,0] in that order. Till we find the
 * the position of A[i] we right shift the elements of A[0...i-1], and once the
 * position is found, we insert A[i] there.
 */
int insertion_sort(int *array, int size);

int main()
{

	int *array = NULL;
	int index, size = 0;
	
	scanf("%d", &size);
	
	array = malloc(sizeof(int) * size);
	if(!array) {
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
			/* swap_position is the possible postion for inserting array[index]
			 */
			swap_position = index;
			/* swap_data contains the element that needs to be inserted into
			 * relative position.
			 */
			swap_data = array[index];
			
			/* find the suitable postion to insert the element in question, at
			 * same time create the a to insert the element in question. */
			while(swap_position >= 0 && swap_data < array[swap_position - 1]) {
				array[swap_position] = array[swap_position -1];
				swap_position -= 1;
			}
			if( swap_position < 0)
				array[0] = swap_data;
			else
				array[swap_position] = swap_data;
		}
	}

	return 0;
}
