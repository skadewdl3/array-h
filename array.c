#include <stdio.h>
#include "array.h"

void print (char el, int index, CharArray arr) {
	printf("(%d): %c\n", index, el);
}

char increment (int element, int index) {
	return (element + index);
}


int filter (char element, int index, CharArray arr) {
	if (element == 'a' || element == 'c') return 0;
	return 1;
}

int main () {
	char numbers[] = {'a', 'b', 'c', 'c', 'd', 'e'};
	char numbers2[] = {'a', 'b'};
	CharArray array = Array_from(numbers, 6);
	CharArray array2 = Array_from(numbers2, 2);

	Array_foreach(array, print);
	printf("\n");

	array = Array_concat(array, array2, 2);

	Array_foreach(array, print);
	printf("\n");

	CharArray filtered = Array_filter(array, filter)

	Array_foreach(filtered, print);
	printf("\n");



	Array_destroy(array);
}	