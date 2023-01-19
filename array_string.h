#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

// Creates an array by allocating memory to it
StringArray StringArray_create (int length) {
	// Allocates [length] * sizeof(char*) bytes of memory and points array.items to it
	StringArray array;
	array.length = length;
	array.used = 0;
	array.items = malloc(length * sizeof(char*));
	if (array.items == NULL) {
		Array_error(MEM_ALLOC_FAIL);
		return array;
	}

	for (int i = 0; i < array.length; i++) {
		array.items[i] = "\0";
	}
	return array;
}

// Creates a new StringArray from an existing array (char* elements[])
StringArray Array_from_string (char** elements, int length) {
	StringArray from = StringArray_create(length);
	for (int i = 0; i < length; i++) {
		from.items[i] = elements[i];
	}
	from.used = length;
	return from;
}

// Resizes the array by allocating/deallocating memory
StringArray Array_resize_string (StringArray array, int resize_factor) {

	// resize_factor > 0 -> allocates more memory to array;
	// resize_factor < 0 -> deallocates some memory from array;

	array.items = realloc(array.items, (array.length + resize_factor) * sizeof(char*));
	if (array.items == NULL) {
		Array_error(MEM_REALLOC_FAIL);
		return array;	
	}
	array.length += resize_factor;
	if (resize_factor > 0) {
		for (int i = array.used; i < array.length; i++) {
			array.items[i] = "\0";
		}	
	}

	return array;	
}

void Array_destroy_string (StringArray array) {
	free(array.items);
}


/* Loops over the array and runs a callback with each turn
   Callback receives the current element and the current index */
void Array_foreach_string (StringArray array, StringArrayForeachFunction function) {
	for (int i = 0; i < array.used; i++) {
		function(array.items[i], i, array);
	}
}

// Adds an element to the end of the array
StringArray Array_push_string (StringArray array, char* element) {
	int insert_index = array.used;
	if (array.length <= array.used) {
		array = Array_resize_string(array, 1);
		insert_index = array.length - 1;
	}
	array.items[insert_index] = element;
	array.used++;
	return array;
}

// Adds an element to the start of the array

// Removes an element from the end of the array

// Checks if element exists in array

/* Loops over the array and runs a callback with each turn
   If callback returns 1, keeps the element in the array. Otherwise, removes it.
   This function does not alter the original array. */



/* Loops over the array and runs a callback with each turn
   Callback is given current element and can make changes to it.
   Callback is expected to return an char*.
   This function does not alter the original array. */

// Return element at specified index from StringArray


/* Sets the element at specified index from StringArray to specified value.
   Returns an error if the array is not long enough. */

// Counts the number of occurences of specified element in IntArray

// Returns subarray made from IntArray from start to end indices (both included)

// Deletes an element from the array. Alters the oriinal array.

/* Insert element at specified index in IntArray.
   If element already exists, it is shifted forward and new element is placed at the index.
   If array isn't long enough, extends the array and places the new element at given index. */

/* A generalised sort function. Accepts a sorter function.
   Provides helper functions for getting, setting and swapping elements in the array
   Does not alter the original array. */

/* PREDEFINED HELPER FUNCTIONS
   These function supplement the main functions of the library. They include pre-written
   function for printing (using Array_foreach), bubble/selection/insertion
   sorts (using Array_sort) */

void STRING_ARRAY_PRINT (char* el, int index, StringArray arr) {
	printf("(%d): %s\n", index, el);
}