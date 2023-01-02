#include <stdio.h>
#include "array.h"

void print (float el, int index, FloatArray arr) {
	printf("(%d): %f\n", index, el);
}

int main () {

	float floats[] = {2, 3.009, 3.008, 6, 5, 7};
	FloatArray array = Array_from(floats, 6);

	Array_foreach(array, print);
	printf("\n");

	FloatArray sorted = Array_sort(array, FLOAT_ARRAY_BUBBLE_SORTER);	
	float item = Array_get(sorted, 5)

	printf("\n\ngetting: %d\n\n", item);
	Array_foreach(sorted, print);
	printf("\n");

	Array_destroy(array);
	Array_destroy(sorted);
}	