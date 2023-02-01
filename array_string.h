#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef struct {
	CharArray* items;
	int used;
	int length;
} StringArray;

typedef void (*StringArrayForeachFunction)(char*, int, StringArray);
typedef char* (*StringArrayMapFunction)(char*, int, StringArray);
typedef int (*StringArrayFilterFunction)(char*, int, StringArray);
typedef void (*StringArraySetFunction) (char*, int);
typedef char* (*StringArrayGetFunction) (int);
typedef void (*StringArraySortFunction)(StringArray, StringArrayGetFunction, StringArraySetFunction, ArraySwapFunction);


// Creates an array by allocating memory to it
StringArray StringArray_create (int length) {
	// Allocates [length] * sizeof(char*) bytes of memory and points array.items to it
	StringArray array;
	array.length = length;
	array.used = 0;
	array.items = malloc(length * sizeof(CharArray));
	if (array.items == NULL) {
		Array_error(MEM_ALLOC_FAIL);
		return array;
	}

	for (int i = 0; i < array.length; i++) {
		CharArray arr = CharArray_create(0);
		array.items[i] = arr;
	}
	return array;
}
	
// Resizes the array by allocating/deallocating memory
StringArray Array_resize_string (StringArray array, int resize_factor) {

	// resize_factor > 0 -> allocates more memory to array;
	// resize_factor < 0 -> deallocates some memory from array;

	array.items = realloc(array.items, (array.length + resize_factor) * sizeof(CharArray));
	if (array.items == NULL) {
		Array_error(MEM_REALLOC_FAIL);
		return array;	
	}
	array.length += resize_factor;
	if (resize_factor > 0) {
		for (int i = array.used; i < array.length; i++) {
			CharArray arr = CharArray_create(0);
			array.items[i] = arr;
		}	
	}
	return array;
}

StringArray Array_from_string (char** elements, int length) {
	StringArray from = StringArray_create(length);
	for (int i = 0; i < length; i++) {
		CharArray el = Array_from_char(elements[i], strlen(elements[i]) + 1);
		el.items[el.length - 1] = '\0'; 
		from.items[i] = el;
	}
	from.used = length;
	return from;
}

void Array_destroy_string (StringArray array) {
	for (int i = 0; i < array.length; i++) {
		Array_destroy_char(array.items[i]);
	}
	free(array.items);
}

StringArray Array_set_string (StringArray array, char* string, int index) {
	if (!(index < array.used)) {
		Array_error(UNUSED_ACCESS);
		return array;
	}
	else if (!(index < array.length) || index < 0) {
		Array_error(OUT_OF_BOUNDS);
		return array;
	}
	else {
		CharArray el = Array_from_char(string, strlen(string) + 1);
		el.items[el.length - 1] = '\0'; 
		array.items[index] = el; 
	}
	return array;
}

char* Array_get_string (StringArray array, int index) {
	if (!(index < array.used)) {
		Array_error(UNUSED_ACCESS);
		return "";
	}
	else if (!(index < array.length) || index < 0) {
		Array_error(OUT_OF_BOUNDS);
		return "";
	}
	else {
		return array.items[index].items;
	}
}


void Array_foreach_string (StringArray array, StringArrayForeachFunction function) {
	for (int i = 0; i < array.used; i++) {
		function(array.items[i].items, i, array);
	}
}

// concat_arr

// concat

// push
// Adds an element to the end of the array
StringArray Array_push_string (StringArray array, char* element) {
	int insert_index = array.used;
	if (array.length <= array.used) {
		array = Array_resize_string(array, 1);
		insert_index = array.length - 1;
	}
	CharArray arr = Array_from_char(element, strlen(element) + 1);
	arr.items[strlen(element)] = '\0';
	array.items[insert_index] = arr;
	array.used++;
	return array;
}

// unshift
StringArray Array_unshift_string (StringArray array, char* element) {
	if (array.used == array.length) {
		array = Array_resize_string(array, 1);	
	}
	for (int i = array.used - 1; i >= 0; i--) {
		CharArray temp = array.items[i + 1];
		array.items[i + 1] = array.items[i];
		array.items[i] = temp;
	}
	CharArray arr = Array_from_char(element, strlen(element) + 1);
	arr.items[strlen(element)] = '\0';
	array.items[0] = arr;
	array.used++;
	return array;
}
// pop
StringArray Array_pop_string (StringArray array) {
	array.used--;
	return array;
}

// exists

// count

// filter 

// map

// copy

// slice
StringArray Array_slice_string (StringArray array, int start, int end) {
	if (start < 0 || !(end < array.used)) {
		Array_error(OUT_OF_BOUNDS);
	}
	StringArray sliced = StringArray_create(end - start + 1);
	for (int i = 0; i <= sliced.length; i++) {
		sliced.items[i] = Array_copy_char(array.items[i + start]); 
	}
	sliced.used = sliced.length;
	return sliced;
}


// delete

// insert

// sort