#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<limits.h>

#define ALGO_TYPE_LINEAR 0
#define ALGO_TYPE_RECURSIVE 1

struct struct_sub_array {
	int* array;
	int start_idx;
	int end_idx;
	int sum;
};
typedef struct struct_sub_array subarray_t;

subarray_t max_sub_array_brute(int *array, int size);
subarray_t max_cross_sub_array(int* array, int start_idx, int mid_idx, int end_idx);
subarray_t max_sub_array_recursive(int* array, int start_idx, int end_idx);
int max_sub_array(int *array, int size, int mode);

int main()
{
	int* array;
	int size;
	int index;
	int mode;

	scanf("%d", &mode);
	scanf("%d", &size);

	array = malloc(sizeof(int) * size);
	if(!array) {
		printf("ERROR: Memory allocation for array\n");
		return 0;
	}
	memset(array, 0, sizeof(int) * size);

	for(index = 0; index < size; index++)
		scanf("%d", &array[index]);

	max_sub_array(array, size, mode);

	free(array);
	return 0;
}

int max_sub_array(int *array, int size, int mode)
{
	subarray_t max_subarray;
	int index;

	max_subarray.array = array;

	if(!array) {
		printf("Error: No Array specified\n");
		return -1;
	}

	if(mode == ALGO_TYPE_LINEAR)
		max_subarray = max_sub_array_brute(array, size);
	/*else
		max_subarray = max_sub_array_recursive(array, 0, size - 1);*/

	printf("max sub-array: array[%d....%d], sum[%d]", max_subarray.start_idx,
			max_subarray.end_idx, max_subarray.sum);
	for(index = max_subarray.start_idx; index <= max_subarray.end_idx; index++)
		printf("%d", array[index]);

	return 0;
}

subarray_t max_sub_array_brute(int* array, int size)
{
	 subarray_t max_subarray;
	 int index;
	 int sum;
	 int end_idx;

	max_subarray.array = array;
	max_subarray.start_idx = -1;
	max_subarray.end_idx = -1;
	max_subarray.sum = INT_MIN;

	if(!array) {
		printf("Error: No Array specified\n");
		return max_subarray;
	}

	for(index = 0; index < size; index++) {
		sum = 0;
		end_idx = index;

		while(end_idx < size) {
			sum += array[end_idx];
			if(max_subarray.sum < sum) {
				max_subarray.sum = sum;
				max_subarray.start_idx = index;
				max_subarray.end_idx = end_idx;
			}
			end_idx += 1;
		}
	}

	return max_subarray;
}

subarray_t max_cross_sub_array(int* array, int start_idx, int mid_idx, int end_idx)
{
	subarray_t cross_sub_array = {array, -1, -1, INT_MIN};
	int index;
	int sum = 0;

	if(!array) {
		printf("ERROR: No Array specified\n");
		return cross_sub_array;
	}

	index = mid_idx;
	while(index >=0) {
		sum += array[index];
		if(sum > cross_sub_array.sum) {
			cross_sub_array.sum = sum;
			cross_sub_array.start_idx = index;
		}
		index -= 1;
	}

	index = mid_idx + 1;
	sum = cross_sub_array.sum;
	cross_sub_array.end_idx = mid_idx;
	while(index <= end_idx) {
		sum += array[index];
		if(sum > cross_sub_array.sum) {
			cross_sub_array.sum =sum;
			cross_sub_array.end_idx = index;
		}
		index += 1;
	}

	return cross_sub_array;
}
