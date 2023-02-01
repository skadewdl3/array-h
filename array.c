#include <stdio.h>
#include "array.h"

void print (int el, int index, IntArray array) {
	printf("\n(%d): %d", index, el);
} 

int modify (int el, int index, IntArray array) {
	return ++el;
}


int main () {

	int integers[] = {1, 2, 3, 4, 56};

	IntArray array = Array_from(integers, 5);

	IntArray mapped = Array_map(array, modify);

	Array_foreach(array, INT_ARRAY_PRINT);
	Array_foreach(mapped, INT_ARRAY_PRINT);


	Array_destroy(array);
	Array_destroy(mapped);


	return 0;
}