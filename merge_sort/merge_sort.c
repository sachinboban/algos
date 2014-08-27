#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int merge_sort(int *array, int start_idx, int end_idx);

int main()
{
	int index, size, *array = NULL;

	/* Read the array size */
	scanf("%d", &size);

	array = (int *)malloc(sizeof(int) * size);
	if(!array) {
		printf("ERROR: malloc()\n");
		return 0;
	}

	/* Read te array */
	for(index = 0; index < size; index += 1)
		scanf("%d", &array[index]);
	
	merge_sort(array, 0, size - 1);

	for(index = 0; index < size; index += 1)
		printf("%d, ", array[index]);
	
	free(array);
	return 0;
}

int merge_sort(int *array, int start_idx, int end_idx)
{
	int mid_idx, size, *temp_array = NULL;
	int index, index1, index2, ret = 0;

	if(!array) {
		printf("[%s][ERROR: No array specified\n", __FUNCTION__);
		return -1;
	}

	if(start_idx == end_idx)
		return 0;
	
	mid_idx = (start_idx + end_idx) / 2;
	
	ret = merge_sort(array, start_idx, mid_idx);
	if(ret) {
		printf("[%s][ERROR]: merge_sort[%d...%d] failed\n", __FUNCTION__,
				start_idx, mid_idx);
		return ret;
	}

	merge_sort(array, mid_idx + 1, end_idx);
	if(ret) {
		printf("[%s][ERROR] merge_sort[%d...%d] failed\n", __FUNCTION__,
				mid_idx + 1, end_idx);
		return ret;
	}

	/* Merging
	 * There are two arrays to be merged A[start_idx1...end_idx1] and 
	 * A[start_idx2...end_idx2]. We merge the two arrays into a third array and
	 * then copy the array back to the original array.
	 */

	size = end_idx - start_idx + 1;			//size of the merged array

	temp_array = (int *)malloc(sizeof(int) * size);
	if(!temp_array) {
		printf("[%s][ERROR] malloc()\n", __FUNCTION__);
		return -1;
	}
	memset(temp_array, 0, sizeof(int) * size);

	index1 = start_idx;
	index2 = mid_idx + 1;

	for(index = 0; index < size; index += 1) {
		if(index1 < 0 || index2 < 0)
			break;

		if(array[index1] < array[index2]) {
			temp_array[index] = array[index1];
			index1 += 1;

			if(index1 > mid_idx)
				index1 = -1;
		} else {
			temp_array[index] = array[index2];
			index2 += 1;

			if(index2 > end_idx)
				index2 = -1;
		}
	}

	while(index1 == -1 && index < size) {
		temp_array[index] = array[index2];
		index += 1;
		index2 += 1;
	}

	while(index2 == -1 && index < size) {
		temp_array[index] = array[index1];
		index += 1;
		index1 += 1;
	}

	for(index1 = start_idx, index = 0; index1 <= end_idx; index1 += 1, index += 1)
		array[index1] =temp_array[index];

	free(temp_array);
	return 0;
}
