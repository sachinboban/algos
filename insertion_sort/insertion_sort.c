#include <stdio.h>
#include <stdlib.h>

int get_smallest_index(int *array, int size, int start_index);
void swap(int *a, int *b);
void insertion_sort(int *array, int size);

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
	
	insertion_sort(array, size);
	
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

void insertion_sort(int *array, int size)
{
	int current_index, temp_small_index;

	for(current_index = 0; current_index < size - 1; ++current_index) {
		temp_small_index = get_smallest_index(array, size, current_index + 1);
		if(array[current_index] > array[temp_small_index])
			swap(&array[current_index], &array[temp_small_index]);
	}
}
