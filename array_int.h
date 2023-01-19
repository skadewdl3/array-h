#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>


// Creates an array by allocating memory to it
IntArray IntArray_create (int length) {
	// Allocates [length] * sizeof(int) bytes of memory and points array.items to it
	IntArray array;
	array.length = length;
	array.used = 0;
	array.items = malloc(length * sizeof(int));
	if (array.items == NULL) {
		Array_error(MEM_ALLOC_FAIL);
		return array;	
	}
	for (int i = 0; i < array.length; i++) {
		array.items[i] = 0;
	}
	return array;	
}

// Creates a new IntArray from an existing array (int elements[])
IntArray Array_from_int (int* elements, int length) {
	IntArray from = IntArray_create(length);
	for (int i = 0; i < length; i++) {
		from.items[i] = elements[i];
	}
	from.used = length;
	return from;
}

// Resizes the array by allocating/deallocating memory
IntArray Array_resize_int (IntArray array, int resize_factor) {

	// resize_factor > 0 -> allocates more memory to array;
	// resize_factor < 0 -> deallocates some memory from array;

	array.items = realloc(array.items, (array.length + resize_factor) * sizeof(int));
	if (array.items == NULL) {
		Array_error(MEM_REALLOC_FAIL);
		return array;	
	}
	array.length += resize_factor;
	if (resize_factor > 0) {
		for (int i = array.used; i < array.length; i++) {
			array.items[i] = 0;
		}	
	}
	return array;
}

// Destroys the array by freeing the memory allocated to it
void Array_destroy_int (IntArray array) {
	free(array.items);
}

// Joins a IntArray to an existing IntArray
IntArray Array_concat_arr_int (IntArray array, IntArray concat, int length) {
	int prev_length = array.length;
	int prev_used = array.used;
	if (prev_used + concat.length > array.length) {
		int resize_factor = prev_used + concat.length - array.length;
		array = Array_resize_int(array, resize_factor); 
	}
	for (int i = 0; i < concat.length; i++) {
		array.items[prev_used + i] = concat.items[i];
	}
	array.used = prev_used + concat.used;
	return array;
}

// Joins an array of integers (int concat[]) to existing IntArray
IntArray Array_concat_int (IntArray array, int* concat, int length) {
	int prev_used = array.used;
	if (prev_used + length > array.length) {
		int resize_factor = prev_used + length - array.length;
		array = Array_resize_int(array, resize_factor); 
	}
	for (int i = 0; i < length; i++) {
		array.items[prev_used + i] = concat[i];
	}
	array.used = prev_used + length;
	return array;
}

/* Loops over the array and runs a callback with each turn
   Callback receives the current element and the current index */
void Array_foreach_int (IntArray array, IntArrayForeachFunction function) {
	for (int i = 0; i < array.used; i++) {
		function(array.items[i], i, array);
	}
}

// Adds an element to the end of the array
IntArray Array_push_int (IntArray array, int element) {
	int insert_index = array.used;
	if (array.length <= array.used) {
		array = Array_resize_int(array, 1);
		insert_index = array.length - 1;
	}
	array.items[insert_index] = element;
	array.used++;
	return array;
}

// Adds an element to the start of the array
IntArray Array_unshift_int (IntArray array, int element) {
	if (array.used == array.length) {
		array = Array_resize_int(array, 1);	
	}
	for (int i = array.used - 1; i >= 0; i--) {
		int temp = array.items[i + 1];
		array.items[i + 1] = array.items[i];
		array.items[i] = temp;
	}
	array.items[0] = element;
	array.used++;
	return array;
}

// Removes an element from the end of the array
IntArray Array_pop_int (IntArray array) {
	array.used--;
	return array;
}

// Checks if element exists in array
int Array_exists_int (IntArray array, int element) {
	int found = 0;
	for (int i = 0; i < array.used; i++) {
		if (array.items[i] == element) {
			found = 1;
			break;
		}
	}
	return found;
}

/* Loops over the array and runs a callback with each turn
   If callback returns 1, keeps the element in the array. Otherwise, removes it.
   This function does not alter the original array. */
IntArray Array_filter_int (IntArray array, IntArrayFilterFunction function) {
	IntArray filtered = IntArray_create(0);
	for (int i = 0; i < array.used; i++) {
		int should_add = function(array.items[i], i, array);
		if (should_add) filtered = Array_push_int(filtered, array.items[i]);
	}
	return filtered;
}

/* Loops over the array and runs a callback with each turn
   Callback is given current element and can make changes to it.
   Callback is expected to return an int.
   This function does not alter the original array. */
IntArray Array_map_int (IntArray array, IntArrayMapFunction function) {
	IntArray mapped = IntArray_create(array.length);
	for (int i = 0; i < array.used; i++) {
		int new_el = function(array.items[i], i, array);
		mapped.items[i] = new_el;
	}
	return mapped;
}

// Makes an exact copy of an IntArray and returns it
IntArray Array_copy_int (IntArray array) {
	int filter (int el, int i, IntArray arr) {
		return 1;
	}
	IntArray copied = Array_filter_int(array, filter);
	copied.used = array.used;
	return copied;
}

// Return element at specified index from IntArray
int Array_get_int (IntArray array, int index) {
	if (!(index < array.used) || index < 0) {
		Array_error(UNUSED_ACCESS);
		return 0;
	}
	return array.items[index];
}

/* Sets the element at specified index from IntArray to specified value.
   Returns an error if the array is not long enough. */
IntArray Array_set_int (IntArray array, int element, int index) {
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
int Array_count_int (IntArray array, int element) {
	int count = 0;
	for (int i = 0; i < array.used; i++) {
		if (array.items[i] == element) count++;
	}
	return count;
}

// Returns subarray made from IntArray from start to end indices (both included)
IntArray Array_slice_int (IntArray array, int start, int end) {
	if (start < 0 || !(end < array.used)) {
		Array_error(OUT_OF_BOUNDS);
	}
	IntArray sliced = IntArray_create(end - start + 1);
	for (int i = 0; i <= sliced.length; i++) {
		sliced.items[i] = array.items[i + start]; 
	}
	sliced.used = sliced.length;
	return sliced;
}

// Deletes an element from the array. Alters the oriinal array.
IntArray Array_delete_int (IntArray array, int index) {
	if (!(index < array.length) || index < 0) {
		Array_error(OUT_OF_BOUNDS);
		return array;
	}
	int filter (int el, int i, IntArray arr) {
		return i != index;
	}
	array = Array_filter_int(array, filter);
	return array;
}

/* Insert element at specified index in IntArray.
   If element already exists, it is shifted forward and new element is placed at the index.
   If array isn't long enough, extends the array and places the new element at given index. */
IntArray Array_insert_int (IntArray array, int element, int index) {
	if (index < 0) {
		Array_error(OUT_OF_BOUNDS);
		return array;
	}
	IntArray inserted = Array_copy_int(array);
	if (index > inserted.length - 1) {
		inserted = Array_resize_int(inserted, index - inserted.length + 1);
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
IntArray Array_sort_int (IntArray array, IntArraySortFunction function) {
	IntArray sorted = IntArray_create(array.length);
	sorted.used = array.used;
	for (int i = 0; i < sorted.length; i++) {
		sorted.items[i] = array.items[i];
	}
	int get (int index) {
		return Array_get_int(sorted, index);
	}
	void set (int element, int index) {
		sorted = Array_set_int(sorted, element, index);
	}
	void swap (int index1, int index2) {
		int temp = sorted.items[index1];
		sorted.items[index1] = sorted.items[index2];
		sorted.items[index2] = temp;
	}
	function(sorted, get, set, swap);
	return sorted;
}


/* PREDEFINED HELPER FUNCTIONS
   These function supplement the main functions of the library. They include pre-written
   function for printing (using Array_foreach), bubble/selection/insertion
   sorts (using Array_sort) */

void INT_ARRAY_PRINT (int el, int index, IntArray arr) {
	printf("(%d): %d\n", index, el);
}

void INT_ARRAY_BUBBLE_SORTER (IntArray sorted, IntArrayGetFunction get, IntArraySetFunction set, ArraySwapFunction swap) {
	for (int i = 0; i < sorted.used; i++) {
		int swaps = 0;		
		for (int j = 0; j < sorted.used - i; j++) {
			if (j != 0) {
				if (get(j) < get(j - 1)) {
					swaps++;
					swap(j, j - 1);
				}
			} 
		}
		if (swaps == 0) break;
	}
}

void INT_ARRAY_SELECTION_SORTER (IntArray sorted, IntArrayGetFunction get, IntArraySetFunction set, ArraySwapFunction swap) {
	for (int i = 0; i < sorted.used - 1; i++) {
		int min_index = i;
		for (int j = i; j < sorted.used; j++) {
			if (get(j) < get(min_index)) min_index = j;
		}
		if (min_index == i) break;
		swap(i, min_index);
	}
}

void INT_ARRAY_INSERTION_SORTER (IntArray sorted, IntArrayGetFunction get, IntArraySetFunction set, ArraySwapFunction swap) {
	for (int i = 1; i < sorted.used; i++) {
		int j = i - 1;
		while (j >= 0 && get(j) < get(j - 1)) {
			swap(j, j - 1);
			j--;
		}
	}
}