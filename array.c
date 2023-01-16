#include <stdio.h>
#include "array.h"

void print (int el, int index, IntArray array) {
	printf("\n(%d): %d", index, el);
}

int main () {


	int integers[] = {1, 2, 3, 4, 5, 6, 7};
	IntArray array = Array_from(integers, 7);

	Array_foreach(array, print);
	printf("\n");

	array = Array_insert(array, 99, 10);


	Array_foreach(array, print);
	printf("\n");

	return 0;
}