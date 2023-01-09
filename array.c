#include <stdio.h>
#include "array.h"

void print (int el, int index, IntArray arr) {
	printf("(%d): %d\n", index, el);
}

int map (int el, int index, IntArray arr) {
	return ++el;
}

int main () {


	int length;
	int sum = 0;
	int integers[] = {1, 4, 5, 10, -1, -100};

	IntArray arr = IntArray_create(5);
	IntArray concat = Array_from(integers, 6);
 	arr = Array_concat(arr, concat, 6);
	IntArray sorted = Array_sort(arr, INT_ARRAY_BUBBLE_SORTER);


	Array_foreach(arr, print);
 	printf("\n\n");
	Array_foreach(sorted, print);

	Array_destroy(arr);
	Array_destroy(sorted);

}	