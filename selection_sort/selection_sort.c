#include <stdio.h>
#include <stdlib.h>

/*
 * get_smallest_index
 * @array
 * @size			size of array
 * @start_index		start index
 *
 * Finds the smallest element in array[start_index...size-1], and returns its
 * index.
 */
int get_smallest_index(int *array, int size, int start_index);

void swap(int *a, int *b);

/*
 * selection_sort
 * @array		array to be sorted
 * @size		size of array
 *
 * Given an array, sort the using insertion sort.
 * T(n) = O(n^2)
 */
void selection_sort(int *array, int size);

int main()
{
	int index, data, size, *array;
	array = NULL;

	printf("Array size?\n");
	scanf("%d", &size);

	array = (int *) malloc(sizeof(int) * size);
	if(!array) {
		printf("Memory error\n");
		return 0;
	}

	printf("Enter array\n");
	for(index = 0; index < size; ++index)
		scanf("%d", &array[index]);
	
	selection_sort(array, size);
	
	printf("Sorted array: ");
	for(index = 0; index < size; ++index)
		printf("%d ", array[index]);
	
	free(array);
	return 0;
}

int get_smallest_index(int *array, int size, int start_index)
{
	int small = start_index;

	if(small == size)
		return small;

	start_index += 1;

	for(; start_index < size; start_index++) {
		if(array[small] > array[start_index])
			small = start_index;
	}

	return small;
}

void swap(int *a, int *b)
{
	int temp = *a;
	*a  = *b;
	*b = temp;
}

void selection_sort(int *array, int size)
{
	int current_index, temp_small_index;

	for(current_index = 0; current_index < size - 1; ++current_index) {
	/* At any iteration current_index find the smallest element in
	 * array[current_index...size-1] and swap it to array[current_index]
	 * At the end of every iteration array[0...current_index] will be sorted.
	 */
		temp_small_index = get_smallest_index(array, size, current_index + 1);
		if(array[current_index] > array[temp_small_index])
			swap(&array[current_index], &array[temp_small_index]);
	}
}
