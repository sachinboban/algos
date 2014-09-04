#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<limits.h>

#define ALGO_TYPE_LINEAR 0
#define ALGO_TYPE_RECURSIVE 1

/*
 * struct_sub_array
 * @array		array pointer
 * @start_idx	starting index of the maximum sub-array
 * @end_idx		ending index of the maximum sub-array
 * @sum			sum of the maximum sub-array
 *
 * structure to represent the maximum sub-array, given by
 * array[start_idx...end_idx]. It is typecasted as subarray_t.
 */
struct struct_sub_array {
	int* array;
	int start_idx;
	int end_idx;
	int sum;
};
typedef struct struct_sub_array subarray_t;

/*
 * max_sub_array_brute
 * @array
 * @size		size of the array
 *
 * find the maximum sub-array of the given array using brute-force approach.
 * Considers all the possible sub-arrays of the given array, and find the
 * maximum.
 * T(n) = O(n*n)
 */
subarray_t max_sub_array_brute(int *array, int size);

/*
 * max_cross_sub_array
 * array
 * start_idx		start index
 * mid_idx			middle index
 * end_idx			end index
 *
 * Find the maximum sub-array of array[start_idx...end_index] which includes
 * array[mid_idx].
 * T(n) = O(n)
 */
subarray_t max_cross_sub_array(int* array, int start_idx, int mid_idx,
								int end_idx);

/*
 * max_sub_array_recursive
 * @array
 * @start_idx		start index
 * @end_idx			end index
 *
 * Finds the maximum sub-array of array[start_idx...end_idx].
 * Split the array into two array[start_idx...mid_idx] and array[mid_idx+1...
 * end_idx]. The maximum subarray can be three ways. It can be completely within
 * the left sub-array, or completely within the right sub-array or can span
 * across both left and right sub-array, i.e. max sub-array incudes
 * array[mid_idx]. The first two cases are solved recursively, while the third
 * case is solved using max_cross_sub_array(). The three solutions are then
 * compared to find the max sub-array.
 * T(n) = 2T(n/2) + O(n); T(n) = theta(nlogn)
 */
subarray_t max_sub_array_recursive(int* array, int start_idx, int end_idx);

/*
 * max_sub_array
 * @array		array
 * @size		size of the array
 * @mode		approach in which the solution must be found. brute-force(0) or
 *				recursive(1)
 *
 * wrapper function for finding the maximum subarray for the given array.
 * Depending on the mode specified ALGO_TYPE_LINEAR or ALGO_TYPE_RECURSIVE, it
 * calls max_sub_array_brute() or max_sub_array_recursive() respectively.
 */
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
	else
		max_subarray = max_sub_array_recursive(array, 0, size - 1);

	printf("max sub-array: array[%d....%d], sum[%d], subarry = ",
			max_subarray.start_idx,	max_subarray.end_idx, max_subarray.sum);
	for(index = max_subarray.start_idx; index <= max_subarray.end_idx; index++)
		printf("%d, ", array[index]);

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

subarray_t max_cross_sub_array(int* array, int start_idx, int mid_idx,
								int end_idx)
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

subarray_t max_sub_array_recursive(int* array, int start_idx, int end_idx)
{
	subarray_t max_subarray_left, max_subarray_right, max_subarray_cross,
				max_subarray = {array, -1, -1, INT_MIN};
	int mid_idx;

	if(!array) {
		printf("ERROR: No Array specified\n");
		return max_subarray;
	}

	if(start_idx == end_idx) {
		max_subarray.start_idx = start_idx;
		max_subarray.end_idx = end_idx;
		max_subarray.sum = array[start_idx];
		return max_subarray;
	}

	mid_idx = (start_idx + end_idx)/2;
	max_subarray_left = max_sub_array_recursive(array, start_idx, mid_idx);
	max_subarray_right = max_sub_array_recursive(array, mid_idx + 1, end_idx);
	max_subarray_cross = max_cross_sub_array(array, start_idx, mid_idx, end_idx);

	if(max_subarray_left.sum > max_subarray_cross.sum) {
		if(max_subarray_left.sum > max_subarray_right.sum)
			max_subarray = max_subarray_left;
		else
			max_subarray = max_subarray_right;
	} else {
		if(max_subarray_cross.sum > max_subarray_right.sum)
			max_subarray = max_subarray_cross;
		else
			max_subarray = max_subarray_right;
	}

	return max_subarray;
}
