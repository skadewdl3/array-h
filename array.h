#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// Array Types
typedef struct {
	int* arr;
	int length;
} IntArray;

typedef struct {
	float* arr;
	int length;
} FloatArray;

typedef struct {
	char* arr;
	int length;
} CharArray;

typedef enum {
	OUT_OF_BOUNDS
} ArrayError;

// Array Function Types
typedef void (*IntArrayForeachFunction) (int, int, IntArray);
typedef void (*FloatArrayForeachFunction)(float, int, FloatArray);
typedef void (*CharArrayForeachFunction)(char, int, CharArray);

typedef int (*IntArrayFilterFunction) (int, int, IntArray);
typedef int (*FloatArrayFilterFunction)(float, int, FloatArray);
typedef int (*CharArrayFilterFunction)(char, int, CharArray);

typedef void (*IntArraySetFunction) (int, int);
typedef void (*FloatArraySetFunction) (float, int);
typedef void (*CharArraySetFunction) (char, int);


typedef int (*IntArrayGetFunction) (int);
typedef float (*FloatArrayGetFunction) (int);
typedef char (*CharArrayGetFunction) (int);

typedef void (*ArraySwapFunction) (int, int);


typedef void (*IntArraySortFunction) (IntArray, IntArrayGetFunction, IntArraySetFunction, ArraySwapFunction);
typedef void (*FloatArraySortFunction)(FloatArray, FloatArrayGetFunction, FloatArraySetFunction, ArraySwapFunction);
typedef void (*CharArraySortFunction)(CharArray, CharArrayGetFunction ,CharArraySetFunction, ArraySwapFunction);

#define Array_resize(array, function) _Generic((array),				\
	IntArray: Array_resize_int,										\
	FloatArray: Array_resize_float,									\
	CharArray: Array_resize_char									\
)(array, function);


#define Array_foreach(array, function) _Generic((array),			\
	IntArray: Array_foreach_int,									\
	FloatArray: Array_foreach_float,								\
	CharArray: Array_foreach_char									\
)(array, function);

#define Array_filter(array, function) _Generic((array),				\
	IntArray: Array_filter_int,										\
	FloatArray: Array_filter_float,									\
	CharArray: Array_filter_char									\
)(array, function);

#define Array_destroy(array) _Generic((array),						\
	IntArray: Array_destroy_int,									\
	FloatArray: Array_destroy_float,								\
	CharArray: Array_destroy_char									\
)(array);


#define Array_push(array, element) _Generic((array),				\
	IntArray: Array_push_int,										\
	FloatArray: Array_push_float,									\
	CharArray: Array_push_char										\
)(array, element);


#define Array_concat(array, elements, length) _Generic((elements),	\
	IntArray: Array_concat_arr_int,									\
	FloatArray: Array_concat_arr_float,								\
	CharArray: Array_concat_arr_char,								\
	int*: Array_concat_int,											\
	float*: Array_concat_float,										\
	char*: Array_concat_char										\
)(array, elements, length);

#define Array_from(elements, length) _Generic((elements),			\
	int*: Array_from_int,											\
	float*: Array_from_float,										\
	char*: Array_from_char											\
)(elements, length);


#define Array_sort(array, sorter) _Generic((array),					\
	IntArray: Array_sort_int,													\
	FloatArray: Array_sort_float,												\
	CharArray: Array_sort_char													\
)(array, sorter);

#define Array_get(array, index) _Generic((array),					\
	IntArray: Array_get_int,													\
	FloatArray: Array_get_float,												\
	CharArray: Array_get_char													\
)(array, index);



void Array_error (ArrayError err) {
	switch (err) {
	case OUT_OF_BOUNDS:
		printf("You tried to acces an element past the arrays length. Use [Array_expand] to increase the length or make sure that your code accesses an element within the bounds of the array.");
	}
}

// Creates an array by allocating memory to it
IntArray IntArray_create (int length) {
	// Allocates [length] * sizeof(int) bytes of memory and points array.arr to it
	IntArray array;
	array.length = length;
	array.arr = malloc(length * sizeof(int));
	for (int i = 0; i < array.length; i++) {
		array.arr[i] = 0;
	}
	return array;	
}
FloatArray FloatArray_create (int length) {
	// Allocates [length] * sizeof(int) bytes of memory and points array.arr to it
	FloatArray array;
	array.length = length;
	array.arr = malloc(length * sizeof(float));
	for (int i = 0; i < array.length; i++) {
		array.arr[i] = 0;
	}
	return array;	
}
CharArray CharArray_create (int length) {
	// Allocates [length] * sizeof(int) bytes of memory and points array.arr to it
	CharArray array;
	array.length = length;
	array.arr = malloc(length * sizeof(char));
	for (int i = 0; i < array.length; i++) {
		array.arr[i] = 0;
	}
	return array;	
}


// Creates a array from an existing array
IntArray Array_from_int (int* elements, int length) {
	IntArray from = IntArray_create(length);
	for (int i = 0; i < length; i++) {
		from.arr[i] = elements[i];
	}
	return from;
}
FloatArray Array_from_float (float* elements, int length) {
	FloatArray from = FloatArray_create(length);
	for (int i = 0; i < length; i++) {
		from.arr[i] = elements[i];
	}
	return from;
}
CharArray Array_from_char (char* elements, int length) {
	CharArray from = CharArray_create(length);
	for (int i = 0; i < length; i++) {
		from.arr[i] = elements[i];
	}
	return from;
}


// Resizes an array by allocation/deallocating memory
IntArray Array_resize_int (IntArray array, int resize_factor) {

	// resize_factor > 0 -> allocates more memory to array;
	// resize_factor < 0 -> deallocates some memory from array;

	array.arr = realloc(array.arr, (array.length + resize_factor) * sizeof(int));
	array.length += resize_factor;
	return array;
}
FloatArray Array_resize_float (FloatArray array, int resize_factor) {

	// resize_factor > 0 -> allocates more memory to array;
	// resize_factor < 0 -> deallocates some memory from array;

	array.arr = realloc(array.arr, (array.length + resize_factor) * sizeof(float));
	array.length += resize_factor;
	return array;
}
CharArray Array_resize_char (CharArray array, int resize_factor) {

	// resize_factor > 0 -> allocates more memory to array;
	// resize_factor < 0 -> deallocates some memory from array;

	array.arr = realloc(array.arr, (array.length + resize_factor) * sizeof(char));
	array.length += resize_factor;
	return array;
}


// Destroys the array by freeing the memory allocated to it
void Array_destroy_int (IntArray array) {
	free(array.arr);
}
void Array_destroy_float (FloatArray array) {
	free(array.arr);
}
void Array_destroy_char (CharArray array) {
	free(array.arr);
}


// Joins an array or Int/Float/CharArray to existing Int/Float/CharArray
IntArray Array_concat_arr_int (IntArray array, IntArray concat, int length) {
	int prev_length = array.length;
	array = Array_resize(array, concat.length);
	for (int i = 0; i < concat.length; i++) {
		array.arr[prev_length + i] = concat.arr[i];
	}
	return array;
}
FloatArray Array_concat_arr_float (FloatArray array, FloatArray concat, int length) {
	int prev_length = array.length;
	array = Array_resize(array, concat.length);
	for (int i = 0; i < concat.length; i++) {
		array.arr[prev_length + i] = concat.arr[i];
	}
	return array;
}
CharArray Array_concat_arr_char (CharArray array, CharArray concat, int length) {
	int prev_length = array.length;
	array = Array_resize(array, concat.length);
	for (int i = 0; i < concat.length; i++) {
		array.arr[prev_length + i] = concat.arr[i];
	}
	return array;
}
IntArray Array_concat_int (IntArray array, int* concat, int length) {
	int prev_length = array.length;
	array = Array_resize(array, length);
	for (int i = 0; i < length; i++) {
		array.arr[prev_length + i] = concat[i];
	}
	return array;
}
FloatArray Array_concat_float (FloatArray array, float* concat, int length) {
	int prev_length = array.length;
	array = Array_resize(array, length);
	for (int i = 0; i < length; i++) {
		array.arr[prev_length + i] = concat[i];
	}
	return array;
}
CharArray Array_concat_char (CharArray array, char* concat, int length) {
	int prev_length = array.length;
	array = Array_resize(array, length);
	for (int i = 0; i < length; i++) {
		array.arr[prev_length + i] = concat[i];
	}
	return array;
}


/* Loops over the array and runs a callback with each turn
   Callback receives the current element and the current index */
void Array_foreach_int (IntArray array, IntArrayForeachFunction function) {
	for (int i = 0; i < array.length; i++) {
		function(array.arr[i], i, array);
	}
}
void Array_foreach_float (FloatArray array, FloatArrayForeachFunction function) {
	for (int i = 0; i < array.length; i++) {
		function(array.arr[i], i, array);
	}
}
void Array_foreach_char (CharArray array, CharArrayForeachFunction function) {
	for (int i = 0; i < array.length; i++) {
		function(array.arr[i], i, array);
	}
}


// Adds an element to the end of the array
IntArray Array_push_int (IntArray array, int element) {
	array = Array_resize(array, 1);
	array.arr[array.length - 1] = element;
	return array;
}
FloatArray Array_push_float (FloatArray array, float element) {
	array = Array_resize(array, 1);
	array.arr[array.length - 1] = element;
	return array;
}
CharArray Array_push_char (CharArray array, char element) {
	array = Array_resize(array, 1);
	array.arr[array.length - 1] = element;
	return array;
}


/* Loops over the array and runs a callback with each turn
   If callback returns 1, keeps the element in the array. Otherwise, removes it.
   This function does not alter the original array. */
IntArray Array_filter_int (IntArray array, IntArrayFilterFunction function) {
	IntArray filtered = IntArray_create(0);
	for (int i = 0; i < array.length; i++) {
		int should_add = function(array.arr[i], i, array);
		if (should_add) filtered = Array_push_int(filtered, array.arr[i]);
	}
	return filtered;
}
FloatArray Array_filter_float (FloatArray array, FloatArrayFilterFunction function) {
	FloatArray filtered = FloatArray_create(0);
	for (int i = 0; i < array.length; i++) {
		int should_add = function(array.arr[i], i, array);
		if (should_add) filtered = Array_push_float(filtered, array.arr[i]);
	}
	return filtered;
}
CharArray Array_filter_char (CharArray array, CharArrayFilterFunction function) {
	CharArray filtered = CharArray_create(0);
	for (int i = 0; i < array.length; i++) {
		int should_add = function(array.arr[i], i, array);
		if (should_add) filtered = Array_push_char(filtered, array.arr[i]);
	}
	return filtered;
}

int Array_get_int (IntArray array, int index) {
	if (!(array.length > index)) {
		Array_error(OUT_OF_BOUNDS);
		return 0;
	}
	return array.arr[index];
}

float Array_get_float (FloatArray array, int index) {
	if (!(array.length > index)) {
		Array_error(OUT_OF_BOUNDS);
		return 0;
	}
	return array.arr[index];
}

char Array_get_char (CharArray array, int index) {
	if (!(array.length > index)) {
		Array_error(OUT_OF_BOUNDS);
		return '\0';
	}
	return array.arr[index];
}

IntArray Array_set_int (IntArray array, int element, int index) {
	if (!(array.length > index)) {
		Array_error(OUT_OF_BOUNDS);
	}
	else {
		array.arr[index] = element;
	}
	return array;
}

FloatArray Array_set_float (FloatArray array, float element, int index) {
	if (!(array.length > index)) {
		Array_error(OUT_OF_BOUNDS);
	}
	else {
		array.arr[index] = element;
	}
	return array;
}

CharArray Array_set_char (CharArray array, char element, int index) {
	if (!(array.length > index)) {
		Array_error(OUT_OF_BOUNDS);
	}
	else {
		array.arr[index] = element;
	}
	return array;
}


IntArray Array_sort_int (IntArray array, IntArraySortFunction function) {
	IntArray sorted = IntArray_create(array.length);
	for (int i = 0; i < sorted.length; i++) {
		sorted.arr[i] = array.arr[i];
	}
	int get (int index) {
		return Array_get_int(sorted, index);
	}
	void set (int element, int index) {
		sorted = Array_set_int(sorted, element, index);
	}
	void swap (int index1, int index2) {
		int temp = sorted.arr[index1];
		sorted.arr[index1] = sorted.arr[index2];
		sorted.arr[index2] = temp;
	}
	function(sorted, get, set, swap);
	return sorted;
}
FloatArray Array_sort_float (FloatArray array, FloatArraySortFunction function) {
	FloatArray sorted = FloatArray_create(array.length);
	for (int i = 0; i < sorted.length; i++) {
		sorted.arr[i] = array.arr[i];
	}
	float get (int index) {
		return Array_get_float(sorted, index);
	}
	void set (float element, int index) {
		sorted = Array_set_float(sorted, element, index);	
	}
	void swap (int index1, int index2) {
		float temp = sorted.arr[index1];
		sorted.arr[index1] = sorted.arr[index2];
		sorted.arr[index2] = temp;
	}
	function(sorted, get, set, swap);
	return sorted;
}
CharArray Array_sort_char (CharArray array, CharArraySortFunction function) {
	CharArray sorted = CharArray_create(array.length);
	for (int i = 0; i < sorted.length; i++) {
		sorted.arr[i] = array.arr[i];
	}
	char get (int index) {
		return Array_get_char(sorted, index);
	}
	void set (char element, int index) {
		sorted = Array_set_char(sorted, element, index);
	}
	void swap (int index1, int index2) {
		char temp = sorted.arr[index1];
		sorted.arr[index1] = sorted.arr[index2];
		sorted.arr[index2] = temp;
	}
	function(sorted, get, set, swap);
	return sorted;
}

void INT_ARRAY_BUBBLE_SORTER (IntArray sorted, IntArrayGetFunction get, IntArraySetFunction set, ArraySwapFunction swap) {
	for (int i = 0; i < sorted.length; i++) {
		int swaps = 0;		
		for (int j = 0; j < sorted.length - i; j++) {
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


void FLOAT_ARRAY_BUBBLE_SORTER (FloatArray sorted, FloatArrayGetFunction get, FloatArraySetFunction set, ArraySwapFunction swap) {
	for (int i = 0; i < sorted.length; i++) {
		int swaps = 0;		
		for (int j = 0; j < sorted.length - i; j++) {
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

void CHAR_ARRAY_BUBBLE_SORTER (CharArray sorted, CharArrayGetFunction get, CharArraySetFunction set, ArraySwapFunction swap) {
	for (int i = 0; i < sorted.length; i++) {
		int swaps = 0;		
		for (int j = 0; j < sorted.length - i; j++) {
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