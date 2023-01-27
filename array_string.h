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
StringArray Array_unshift_string (StringArray array, char* element) {
	if (array.used == array.length) {
		array = Array_resize_string(array, 1);	
	}
	for (int i = array.used - 1; i >= 0; i--) {
		char* temp = array.items[i + 1];
		array.items[i + 1] = array.items[i];
		array.items[i] = temp;
	}
	array.items[0] = element;
	array.used++;
	return array;
}


// Removes an element from the end of the array
StringArray Array_pop_string (StringArray array) {
	array.used--;
	return array;
}

// Checks if element exists in array
int Array_exists_string (StringArray array, char* element) {
	int found = 0;
	for (int i = 0; i < array.used; i++) {
		if (strcmp(array.items[i], element) == 0) {
			found = 1;
			break;
		}
	}
	return found;
}

/* Loops over the array and runs a callback with each turn
   If callback returns 1, keeps the element in the array. Otherwise, removes it.
   This function does not alter the original array. */
StringArray Array_filter_string (StringArray array, StringArrayFilterFunction function) {
	StringArray filtered = StringArray_create(0);
	for (int i = 0; i < array.used; i++) {
		int should_add = function(array.items[i], i, array);
		if (should_add) filtered = Array_push_string(filtered, array.items[i]);
	}
	return filtered;
}


/* Loops over the array and runs a callback with each turn
   Callback is given current element and can make changes to it.
   Callback is expected to return an char*.
   This function does not alter the original array. */
StringArray Array_map_string (StringArray array, StringArrayMapFunction function) {
	StringArray mapped = StringArray_create(0);
	for (int i = 0; i < array.used; i++) {
		char* new_el = function(array.items[i], i, array);
		printf("\n%s", new_el);
		// mapped = Array_push_string(mapped, new_el);
	}
	return mapped;
}
// Makes an exact copy of an IntArray and returns it

StringArray Array_copy_string (StringArray array) {
	int filter (char* el, int i, StringArray arr) {
		return 1;
	}
	StringArray copied = Array_filter_string(array, filter);
	copied.used = array.used;
	return copied;
}

// Return element at specified index from StringArray
char* Array_get_string (StringArray array, int index) {
	if (!(index < array.used) || index < 0) {
		Array_error(UNUSED_ACCESS);
		return 0;
	}
	return array.items[index];
}

/* Sets the element at specified index from StringArray to specified value.
   Returns an error if the array is not long enough. */
StringArray Array_set_string (StringArray array, char* element, int index) {
	if (!(index < array.used)) {
		Array_error(UNUSED_ACCESS);
		return array;
	}
	else if (!(index < array.length) || index < 0) {
		Array_error(OUT_OF_BOUNDS);
		return array;
	}
	if (index > array.used - 1) {
		array.used = index + 1;
	}
	array.items[index] = element;
	return array;
}

// Counts the number of occurences of specified element in IntArray
int Array_count_string (StringArray array, char* element) {
	int count = 0;
	for (int i = 0; i < array.used; i++) {
		if (strcmp(array.items[i], element) == 0) count++;
	}
	return count;
}

// Returns subarray made from IntArray from start to end indices (both included)
StringArray Array_slice_string (StringArray array, int start, int end) {
	if (start < 0 || !(end < array.used)) {
		Array_error(OUT_OF_BOUNDS);
	}
	StringArray sliced = StringArray_create(end - start + 1);
	for (int i = 0; i <= sliced.length; i++) {
		sliced.items[i] = array.items[i + start]; 
	}
	sliced.used = sliced.length;
	return sliced;
}

// Deletes an element from the array. Alters the oriinal array.
StringArray Array_delete_string (StringArray array, int index) {
	if (!(index < array.length) || index < 0) {
		Array_error(OUT_OF_BOUNDS);
		return array;
	}
	int filter (char* el, int i, StringArray arr) {
		return i != index;
	}
	array = Array_filter_string(array, filter);
	return array;
}

/* Insert element at specified index in StringArray.
   If element already exists, it is shifted forward and new element is placed at the index.
   If array isn't long enough, extends the array and places the new element at given index. */
StringArray Array_insert_string (StringArray array, char* element, int index) {
	if (index < 0) {
		Array_error(OUT_OF_BOUNDS);
		return array;
	}
	StringArray inserted = Array_copy_string(array);
	if (index > inserted.length - 1) {
		inserted = Array_resize_string(inserted, index - inserted.length + 1);
		inserted.used = index + 1;
	}
	else {
		inserted.used++;
	}
	for (int i = index; i < inserted.used; i++) {
		inserted.items[i + 1] = array.items[i];
	}
	inserted.items[index] = element;
	return inserted;
}


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