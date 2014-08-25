#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define ALGO_TYPE_LINEAR 0
#define ALGO_TYPE_RECURSIVE 1

struct struct_sub_array {
	int* array;
	int start_idx;
	int end_idx;
	int sum;
};
typedef struct_sub_array subarray_t;

subarray_t max_sub_array_brute(int *array, int size);
subarray_t max_cross_sub_array(int* array, int start_idx, int end_idx);
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
		printf("ERROR: malloc()\n");
		return 0;
	}
	memset(array, 0, sizeof(int) * size);

	for(index = 0; index < size; index++)
		scanf("%d", &array[index]);

	max_sub_array(array, size);

	free(array);
	return 0;
}
