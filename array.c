#include <stdio.h>
#include "array.h"

void print (char* el, int index, StringArray array) {
	printf("\n(%d): %s", index, el);
}

int filter (char* el, int index, StringArray array) {
	return index == 0;
}

char* map (char* el, int index, StringArray array) {
	char copy[100];
	strcpy(copy, el);
	printf("\n%s", copy);
	return el;
}
 
int main () {


	char* strings[] = {"Soham", "Karandikar", "Hello", "World"};
	StringArray array = Array_from(strings, 4);

	StringArray mapped = Array_map(array, map);

	Array_foreach(array, print);
	printf("\n");
	Array_foreach(mapped, print);
	printf("\n");

	Array_destroy(array);
	Array_destroy(mapped);

	return 0;
}