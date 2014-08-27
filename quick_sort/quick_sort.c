#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int swap(int *a, int *b);
int quick_sort(int *array, int start_idx, int end_idx);

int main()
{
	int *array = NULL;
	int index, size = 0;

	scanf("%d", &size);

	array = (int *)malloc(sizeof(int) * size);
	if(!array) {
		printf("[%s:%d][ERROR] malloc()\n", __FUNCTION__, __LINE__);
		return 0;
	}

	for(index = 0; index < size; index += 1)
		scanf("%d", &array[index]);
	
	quick_sort(array, 0, size - 1);

	for(index = 0; index < size; index += 1)
		printf("%d ", array[index]);
	
	free(array);
	return 0;
}

int swap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;

	return 0;
}

int quick_sort(int *array, int start_idx, int end_idx)
{
	int index, pivot, ret = 0;
	int	small_array_end;	//Represents the right end of elements < pivot
	int large_array_end;	//Represents the right end of elements > pivot

	if(!array)
		return -1;
	
	if(start_idx == end_idx)
		return ret;
	
	pivot = array[end_idx];
	small_array_end = -1;
	large_array_end = 0;

	for(; large_array_end < end_idx; large_array_end += 1) {
		if(array[large_array_end] < pivot) {
			small_array_end += 1;
			swap(&array[small_array_end], &array[large_array_end]);
		}
	}

	swap(&array[small_array_end + 1], &array[end_idx]);
	
	ret = quick_sort(array, start_idx, small_array_end);
	if(ret) {
		printf("[%s:%d][ERROR] failed[%d]\n", __FUNCTION__, __LINE__, ret);
		return ret;
	}

	ret = quick_sort(array, small_array_end + 2, end_idx);
	if(ret) {
		printf("[%s:%d][ERROR] failed[%d]\n", __FUNCTION__, __LINE__, ret);
		return ret;
	}

	return ret;
}
