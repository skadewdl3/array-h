#include <stdio.h>
#include "array.h"

int map (int el, int index, IntArray array) {
	return el/2;
}

int main () {

	int integers[] = {1, 2, 3, 4, 5, 6};


	IntArray array = Array_from(integers, 6);

	IntArray mapped = Array_map(array, map);




	Array_foreach(array, INT_ARRAY_PRINT);
	printf("\n");

	Array_foreach(mapped, INT_ARRAY_PRINT);

	return 0;
}

