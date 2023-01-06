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

	int integers[] = {-1, 3, 0, 8, 88, -103};

	IntArray array = Array_from(integers, 6);

	printf("\n");

	IntArray mapped = Array_map(array, map);
	Array_foreach(mapped, print);
	printf("\n");

	Array_destroy(array);
	Array_destroy(mapped);

}	