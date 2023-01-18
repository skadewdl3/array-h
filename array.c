#include <stdio.h>
#include "array.h"

void print (char* el, int index, StringArray array) {
	printf("\n(%d): %s", index, el);
}

int main () {


	char* strings[] = {"Soham", "Karandikar", "Hello", "World"};
	StringArray array = Array_from(strings, 4);

	array = Array_resize(array, 1);

	Array_foreach(array, print);
	return 0;
}