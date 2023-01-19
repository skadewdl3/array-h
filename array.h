#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    int* items;
    int length;
    int used;
} IntArray;

IntArray Array_create_int (int length)
{
	IntArray a;
	a.items = malloc(sizeof(int) * length);
	a.length = length;
	a.used = 0;
	for (int i = 0; i < length;i++)
    {
        a.items[i] = 0;
    }
	return a;
}


void Array_print_int (IntArray a) {
	for (int i = 0; i < a.used; i++) {
		printf("\n(%d): %d", i, a.items[i]);
	}
}

IntArray Array_set_int(IntArray a, int element, int index) {
	a.items[index] =  element;
	if (index > a.used) {
		a.used = index + 1;
	}
	return a;
}
