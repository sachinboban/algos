#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LEFT(x) 	2*x		//Left child of a node
#define RIGHT(x) 	2*x + 1	//Right child of a node
#define ROOT		0		//Root of the heap

/*
 * struct_heap_t
 * @array		array containing the heap.
 * @size		size allocated to the array in memory
 * @heap_size	size of the heap
 */
struct struct_heap_t {
	int *array;
	int size;
	int heap_size;
};
typedef struct struct_heap_t heap_t;

void swap(int *a, int *b);

/*
 * max_heapify
 * @heap 		array
 * @index 		index at which maxheap property must be applied(ensured)
 *
 * Ensure maxheap property at the node mentioned by the index.
 *
 * Compares the value of a node and its two child nodes(if any).
 * If heap property is not satisfied, the value of the node is swapped with
 * largest among the three, and the max_heapify() subroutine is applied at the
 * new index of the node.
 */
int max_heapify(heap_t heap, int index);

/*
 * build_max_heap
 * @heap 		array of elments which must built to a maxheap
 *
 * Builds a maxheap for the array given.
 *
 * For any heap, elements floor(n/2)+1.....n represents the leaf nodes.
 * Starting with n/2 down to 0 we apply max_heapify() to ensure that all the
 * nodes of the heap satisfies maxheap property.
 */
int build_max_heap(heap_t heap);

/*
 * heap_sort
 * @heap		array to be sorted.
 *
 * Sort the array by converting it to a maxheap.
 *
 * Build the maxheap for the given array. By maxheap property, root will hold
 * the largest element in the heap. The root value is then swapped with the
 * last element in the array. The array is decremented so that the so sorted
 * value is not part of the rest of the heap. max_heapify is then applied on
 * the root to get the next largest element.
 */
int heap_sort(heap_t heap);

int main()
{
	int index;
	heap_t heap;

	scanf("%d", &heap.size);
	heap.heap_size = heap.size;

	heap.array = (int *)malloc(sizeof(int) * heap.size);
	if(!heap.array) {
		printf("ERROR: malloc()\n");
		return 0;
	}
	memset(heap.array, 0, sizeof(int) * heap.size);

	for(index = 0; index < heap.size; index += 1)
		scanf("%d", &(heap.array[index]));

	printf("\nInput array: ");
	for(index = 0; index < heap.size; index += 1)
		printf("%d ", heap.array[index]);

	heap_sort(heap);
	
	printf("\nSorted array: ");
	for(index = 0; index < heap.size; index += 1)
		printf("%d ", heap.array[index]);

	free(heap.array);
	return 0;
}

int heap_sort(heap_t heap)
{
	int index, ret = 0;
	int *array = heap.array;

	if(!array) {
		printf("ERROR: No array specified\n");
		return -1;
	}

	ret = build_max_heap(heap);
	if(ret)
		return ret;

	for(index = heap.heap_size; index > 0; index -= 1) {
		swap(&array[ROOT], &array[heap.heap_size -1]);
		heap.heap_size -= 1;
		max_heapify(heap, ROOT);
	}

	return ret;
}

int build_max_heap(heap_t heap)
{
	int index, ret = 0;

	if(!heap.array) {
		printf("ERROR: No array specified\n");
		return -1;
	}

	index = (heap.heap_size - 1) / 2;

	for(; index >= 0; index -= 1) {
		ret = max_heapify(heap, index);
		if(ret)
			return ret;
	}

	return ret;
}

int max_heapify(heap_t heap, int index)
{
	int left, right, largest, ret = 0;
	int *array = heap.array;

	if(!array) {
		printf("ERROR: No array specified\n");
		return -1;
	}

	largest = index;

	/* Check whether maxheap property holds */
	/* Check whether the node has both child nodes. If none, then do nothing */
	if(RIGHT(index) >= heap.heap_size && LEFT(index) >= heap.heap_size)
		return ret;
	/* Check if there is only one child node */
	else if(RIGHT(index) >= heap.heap_size) {
		if(array[index] < left)
			largest = LEFT(index);
	} else {
	/* Node has both left and right children*/
		left = array[LEFT(index)];
		right = array[RIGHT(index)];

		if(left > array[index] && left > right)
			largest = LEFT(index);
		else if(right > array[index] && right > left)
			largest = RIGHT(index);
	}

	/* If maxproperty holds at index, then do nothing, else swap and apply
	 * max_heapify at the new location */
	if(largest != index) {
		swap(&array[index], &array[largest]);
		ret = max_heapify(heap, largest);
	}

	return 0;
}

void swap(int *a, int *b) {
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
