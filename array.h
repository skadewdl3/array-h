#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "debug.h"

#define RESET   "\033[0m"			// Reset color to default
#define BLACK   "\033[30m"      	// Black
#define RED     "\033[31m"      	// Red
#define GREEN   "\033[32m"      	// Green
#define YELLOW  "\033[33m"      	// Yellow
#define BLUE    "\033[34m"      	// Blue
#define MAGENTA "\033[35m"      	// Magenta
#define CYAN    "\033[36m"      	// Cyan
#define WHITE   "\033[37m"      	// White

// Array Types
typedef struct {
	int* items;
	int used;
	int length;
} IntArray;

typedef struct {
	float* items;
	int used;
	int length;
} FloatArray;

typedef struct {
	char* items;
	int used;
	int length;
} CharArray;

typedef enum {
	OUT_OF_BOUNDS, MEM_ALLOC_FAIL, MEM_REALLOC_FAIL
} ArrayError;

// Array Function Types
typedef void (*IntArrayForeachFunction) (int, int, IntArray);
typedef void (*FloatArrayForeachFunction)(float, int, FloatArray);
typedef void (*CharArrayForeachFunction)(char, int, CharArray);


typedef int (*IntArrayMapFunction) (int, int, IntArray);
typedef int (*FloatArrayMapFunction)(float, int, FloatArray);
typedef int (*CharArrayMapFunction)(char, int, CharArray);

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
	IntArray: Array_resize_int,												\
	FloatArray: Array_resize_float,											\
	CharArray: Array_resize_char												\
)(array, function);


#define Array_foreach(array, function) _Generic((array),				\
	IntArray: Array_foreach_int,												\
	FloatArray: Array_foreach_float,											\
	CharArray: Array_foreach_char												\
)(array, function);

#define Array_filter(array, function) _Generic((array),				\
	IntArray: Array_filter_int,												\
	FloatArray: Array_filter_float,											\
	CharArray: Array_filter_char												\
)(array, function);

#define Array_destroy(array) _Generic((array),							\
	IntArray: Array_destroy_int,												\
	FloatArray: Array_destroy_float,											\
	CharArray: Array_destroy_char												\
)(array);


#define Array_push(array, element) _Generic((array),					\
	IntArray: Array_push_int,													\
	FloatArray: Array_push_float,												\
	CharArray: Array_push_char													\
)(array, element);


#define Array_unshift(array, element) _Generic((array),				\
	IntArray: Array_unshift_int,												\
	FloatArray: Array_unshift_float,											\
	CharArray: Array_unshift_char												\
)(array, element);

#define Array_concat(array, elements, length) _Generic((elements),\
	IntArray: Array_concat_arr_int,											\
	FloatArray: Array_concat_arr_float,										\
	CharArray: Array_concat_arr_char,										\
	int*: Array_concat_int,														\
	float*: Array_concat_float,												\
	char*: Array_concat_char													\
)(array, elements, length);

#define Array_from(elements, length) _Generic((elements),			\
	int*: Array_from_int,														\
	float*: Array_from_float,													\
	char*: Array_from_char														\
)(elements, length);

#define Array_copy(elements) _Generic((elements),						\
	IntArray: Array_copy_int,														\
	FloatArray: Array_copy_float,													\
	CharArray: Array_copy_char														\
)(elements);

#define Array_sort(array, sorter) _Generic((array),					\
	IntArray: Array_sort_int,													\
	FloatArray: Array_sort_float,												\
	CharArray: Array_sort_char													\
)(array, sorter);

#define Array_get(array, index) _Generic((array),						\
	IntArray: Array_get_int,													\
	FloatArray: Array_get_float,												\
	CharArray: Array_get_char													\
)(array, index);


#define Array_set(array, element, index) _Generic((array),			\
	IntArray: Array_set_int,													\
	FloatArray: Array_set_float,												\
	CharArray: Array_set_char													\
)(array, element, index);


#define Array_exists(array, element) _Generic((array),				\
	IntArray: Array_exists_int,												\
	FloatArray: Array_exists_float,											\
	CharArray: Array_exists_char												\
)(array, element);


#define Array_count(array, element) _Generic((array),					\
	IntArray: Array_count_int,													\
	FloatArray: Array_count_float,											\
	CharArray: Array_count_char												\
)(array, element);


#define Array_slice(array, start, end) _Generic((array),				\
	IntArray: Array_slice_int,													\
	FloatArray: Array_slice_float,											\
	CharArray: Array_slice_char												\
)(array, start, end);

#define Array_map(array, map) _Generic((array),							\
	IntArray: Array_map_int,													\
	FloatArray: Array_map_float,												\
	CharArray: Array_map_char													\
)(array, map);

#define Array_pop(array) _Generic((array),								\
	IntArray: Array_pop_int,													\
	FloatArray: Array_pop_float,												\
	CharArray: Array_pop_char													\
)(array);


#define Array_delete(array, index) _Generic((array),					\
	IntArray: Array_delete_int,												\
	FloatArray: Array_delete_float,											\
	CharArray: Array_delete_char												\
)(array, index);


#define Array_insert(array, element, index) _Generic((array),							\
	IntArray: Array_insert_int,												\
	FloatArray: Array_insert_float,											\
	CharArray: Array_insert_char												\
)(array, element, index);


void Array_error (ArrayError err) {
	switch (err) {
	case OUT_OF_BOUNDS:
		printf(RED "\nLogical Error: [OUT_OF_BOUNDS]\n");
		printf(YELLOW "Invalid index! You tried to access a negative index, or an index past the arrays length. Use [Array_resize] to increase the length or make sure that your code accesses an element within the bounds of the array.\n" RESET);
		break;
	case MEM_ALLOC_FAIL:
		printf(RED "\nRuntime Error: [MEM_ALLOC_FAIL]\n");
		printf(YELLOW "Memory allocation using malloc failed." RESET);
		break;
	case MEM_REALLOC_FAIL:
		printf(RED "\nRuntime Error: [MEM_REALLOC_FAIL]\n");
		printf(YELLOW "Memory reallocation using realloc failed." RESET);
		break;
	}
}

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
FloatArray FloatArray_create (int length) {
	// Allocates [length] * sizeof(int) bytes of memory and points array.items to it
	FloatArray array;
	array.length = length;
	array.used = 0;
	array.items = malloc(length * sizeof(float));
	if (array.items == NULL) {
		Array_error(MEM_ALLOC_FAIL);
		return array;	
	}
	for (int i = 0; i < array.length; i++) {
		array.items[i] = 0;
	}
	return array;	
}
CharArray CharArray_create (int length) {
	// Allocates [length] * sizeof(int) bytes of memory and points array.items to it
	CharArray array;
	array.length = length;
	array.used = 0;
	array.items = malloc(length * sizeof(char));
	if (array.items == NULL) {
		Array_error(MEM_ALLOC_FAIL);
		return array;	
	}
	for (int i = 0; i < array.length; i++) {
		array.items[i] = 0;
	}
	return array;	
}


// Creates a array from an existing array
IntArray Array_from_int (int* elements, int length) {
	IntArray from = IntArray_create(length);
	for (int i = 0; i < length; i++) {
		from.items[i] = elements[i];
	}
	from.used = length;
	return from;
}
FloatArray Array_from_float (float* elements, int length) {
	FloatArray from = FloatArray_create(length);
	for (int i = 0; i < length; i++) {
		from.items[i] = elements[i];
	}
	from.used = length;
	return from;
}
CharArray Array_from_char (char* elements, int length) {
	CharArray from = CharArray_create(length);
	for (int i = 0; i < length; i++) {
		from.items[i] = elements[i];
	}
	from.used = length;
	return from;
}
IntArray Array_from_int_arr (IntArray elements, int length);


// Resizes an array by allocation/deallocating memory
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
FloatArray Array_resize_float (FloatArray array, int resize_factor) {

	// resize_factor > 0 -> allocates more memory to array;
	// resize_factor < 0 -> deallocates some memory from array;

	array.items = realloc(array.items, (array.length + resize_factor) * sizeof(float));
	if (array.items == NULL) {
		Array_error(MEM_REALLOC_FAIL);
		return array;	
	}
	if (resize_factor > 0) {
		for (int i = array.used; i < array.length; i++) {
			array.items[i] = 0;
		}	
	}

	array.length += resize_factor;
	return array;
}
CharArray Array_resize_char (CharArray array, int resize_factor) {

	// resize_factor > 0 -> allocates more memory to array;
	// resize_factor < 0 -> deallocates some memory from array;

	array.items = realloc(array.items, (array.length + resize_factor) * sizeof(char));
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
void Array_destroy_float (FloatArray array) {
	free(array.items);
}
void Array_destroy_char (CharArray array) {
	free(array.items);
}


// Joins an array or Int/Float/CharArray to existing Int/Float/CharArray
IntArray Array_concat_arr_int (IntArray array, IntArray concat, int length) {
	int prev_length = array.length;
	int prev_used = array.used;
	if (prev_used + concat.length > array.length) {
		int resize_factor = prev_used + concat.length - array.length;
		array = Array_resize(array, resize_factor); 
	}
	for (int i = 0; i < concat.length; i++) {
		array.items[prev_used + i] = concat.items[i];
	}
	array.used = prev_used + concat.used;
	return array;
}
FloatArray Array_concat_arr_float (FloatArray array, FloatArray concat, int length) {
	int prev_length = array.length;
	int prev_used = array.used;
	if (prev_used + concat.length > array.length) {
		int resize_factor = prev_used + concat.length - array.length;
		array = Array_resize(array, resize_factor); 
	}
	for (int i = 0; i < concat.length; i++) {
		array.items[prev_used + i] = concat.items[i];
	}
	array.used = prev_used + concat.used;
	return array;
}
CharArray Array_concat_arr_char (CharArray array, CharArray concat, int length) {
	int prev_length = array.length;
	int prev_used = array.used;
	if (prev_used + concat.length > array.length) {
		int resize_factor = prev_used + concat.length - array.length;
		array = Array_resize(array, resize_factor); 
	}
	for (int i = 0; i < concat.length; i++) {
		array.items[prev_used + i] = concat.items[i];
	}
	array.used = prev_used + concat.used;
	return array;
}
IntArray Array_concat_int (IntArray array, int* concat, int length) {
	int prev_used = array.used;
	if (prev_used + length > array.length) {
		int resize_factor = prev_used + length - array.length;
		array = Array_resize(array, resize_factor); 
	}
	for (int i = 0; i < length; i++) {
		array.items[prev_used + i] = concat[i];
	}
	array.used = prev_used + length;
	return array;
}

FloatArray Array_concat_float (FloatArray array, float* concat, int length) {
	int prev_used = array.used;
	if (prev_used + length > array.length) {
		int resize_factor = prev_used + length - array.length;
		array = Array_resize(array, resize_factor); 
	}
	for (int i = 0; i < length; i++) {
		array.items[prev_used + i] = concat[i];
	}
	array.used = prev_used + length;
	return array;
}
CharArray Array_concat_char (CharArray array, char* concat, int length) {
	int prev_used = array.used;
	if (prev_used + length > array.length) {
		int resize_factor = prev_used + length - array.length;
		array = Array_resize(array, resize_factor); 
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
void Array_foreach_float (FloatArray array, FloatArrayForeachFunction function) {
	for (int i = 0; i < array.used; i++) {
		function(array.items[i], i, array);
	}
}
void Array_foreach_char (CharArray array, CharArrayForeachFunction function) {
	for (int i = 0; i < array.used; i++) {
		function(array.items[i], i, array);
	}
}


// Adds an element to the end of the array
IntArray Array_push_int (IntArray array, int element) {
	int insert_index = array.used;
	if (array.length <= array.used) {
		array = Array_resize(array, 1);
		insert_index = array.length - 1;
	}
	array.items[insert_index] = element;
	array.used++;
	return array;
}
FloatArray Array_push_float (FloatArray array, float element) {
	int insert_index = array.used;
	if (array.length <= array.used) {
		array = Array_resize(array, 1);
		insert_index = array.length - 1;
	}
	array.items[insert_index] = element;
	array.used++;
	return array;
}
CharArray Array_push_char (CharArray array, char element) {
	int insert_index = array.used;
	if (array.length <= array.used) {
		array = Array_resize(array, 1);
		insert_index = array.length - 1;
	}
	array.items[insert_index] = element;
	array.used++;
	return array;
}

IntArray Array_unshift_int (IntArray array, int element) {
	if (array.used == array.length) {
		array = Array_resize(array, 1);	
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

// Adds element to the start of the array
FloatArray Array_unshift_float (FloatArray array, float element) {
	if (array.used == array.length) {
		array = Array_resize(array, 1);	
	}
	for (int i = array.used - 1; i >= 0; i--) {
		float temp = array.items[i + 1];
		array.items[i + 1] = array.items[i];
		array.items[i] = temp;
	}
	array.items[0] = element;
	array.used++;
	return array;

}

CharArray Array_unshift_char (CharArray array, char element) {
	if (array.used == array.length) {
		array = Array_resize(array, 1);	
	}
	for (int i = array.used - 1; i >= 0; i--) {
		char temp = array.items[i + 1];
		array.items[i + 1] = array.items[i];
		array.items[i] = temp;
	}
	array.items[0] = element;
	array.used++;
	return array;
}

IntArray Array_pop_int (IntArray array) {
	array.used--;
	return array;
}


FloatArray Array_pop_float (FloatArray array) {
	array.used--;
	return array;
}


CharArray Array_pop_char (CharArray array) {
	array.used--;
	return array;	
}

// Checks if at least one occurence of element is in array
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

int Array_exists_float (FloatArray array, float element) {
	int found = 0;
	for (int i = 0; i < array.used; i++) {
		if (array.items[i] == element) {
			found = 1;
			break;
		}
	}
	return found;
}

int Array_exists_char (CharArray array, char element) {
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
		if (should_add) filtered = Array_push(filtered, array.items[i]);
	}
	return filtered;
}
FloatArray Array_filter_float (FloatArray array, FloatArrayFilterFunction function) {
	FloatArray filtered = FloatArray_create(0);
	for (int i = 0; i < array.used; i++) {
		int should_add = function(array.items[i], i, array);
		if (should_add) filtered = Array_push(filtered, array.items[i]);
	}
	return filtered;
}
CharArray Array_filter_char (CharArray array, CharArrayFilterFunction function) {
	CharArray filtered = CharArray_create(0);
	for (int i = 0; i < array.used; i++) {
		int should_add = function(array.items[i], i, array);
		if (should_add) filtered = Array_push(filtered, array.items[i]);
	}
	return filtered;
}

IntArray Array_map_int (IntArray array, IntArrayMapFunction function) {
	IntArray mapped = IntArray_create(array.length);
	for (int i = 0; i < array.used; i++) {
		int new_el = function(array.items[i], i, array);
		mapped.items[i] = new_el;
	}
	return mapped;
}
FloatArray Array_map_float (FloatArray array, FloatArrayMapFunction function) {
	FloatArray mapped = FloatArray_create(array.length);
		for (int i = 0; i < array.used; i++) {
		float new_el = function(array.items[i], i, array);
		mapped.items[i] = new_el;
	}
	return mapped;
}
CharArray Array_map_char (CharArray array, CharArrayMapFunction function) {
	CharArray mapped = CharArray_create(array.length);
		for (int i = 0; i < array.used; i++) {
		char new_el = function(array.items[i], i, array);
		mapped.items[i] = new_el;
	}
	return mapped;
}

IntArray Array_copy_int (IntArray array) {
	int filter (int el, int i, IntArray arr) {
		return 1;
	}
	IntArray copied = Array_filter(array, filter);
	return copied;
}
FloatArray Array_copy_float (FloatArray array) {
	int filter (float el, int i, FloatArray arr) {
		return 1;
	}

	FloatArray copied = Array_filter(array, filter);
	return copied;
}
CharArray Array_copy_char (CharArray array) {
	int filter (char el, int i, CharArray arr) {
		return 1;
	}
	CharArray copied = Array_filter(array, filter);
	return copied;
}

int Array_get_int (IntArray array, int index) {
	if (!(index < array.used) || index < 0) {
		Array_error(OUT_OF_BOUNDS);
		return 0;
	}
	return array.items[index];
}

float Array_get_float (FloatArray array, int index) {
	if (!(index < array.used) || index < 0) {
		Array_error(OUT_OF_BOUNDS);
		return 0;
	}
	return array.items[index];
}

char Array_get_char (CharArray array, int index) {
	if (!(index < array.used) || index < 0) {
		Array_error(OUT_OF_BOUNDS);
		return '\0';
	}
	return array.items[index];
}

IntArray Array_set_int (IntArray array, int element, int index) {
	if (!(index < array.used) || index < 0) {
		Array_error(OUT_OF_BOUNDS);
	}
	if (index > array.used - 1) {
		array.used = index + 1;
	}
	array.items[index] = element;
	return array;
}

FloatArray Array_set_float (FloatArray array, float element, int index) {
	if (!(index < array.used) || index < 0) {
		Array_error(OUT_OF_BOUNDS);
	}
	else {
		array.items[index] = element;
	}
	return array;
}

CharArray Array_set_char (CharArray array, char element, int index) {
	if (!(index < array.used) || index < 0) {
		Array_error(OUT_OF_BOUNDS);
	}
	else {
		array.items[index] = element;
	}
	return array;
}

int Array_count_int (IntArray array, int element) {
	int count = 0;
	for (int i = 0; i < array.used; i++) {
		if (array.items[i] == element) count++;
	}
	return count;
}


int Array_count_float (FloatArray array, float element) {
	int count = 0;
	for (int i = 0; i < array.used; i++) {
		if (array.items[i] == element) count++;
	}
	return count;
}


int Array_count_char (CharArray array, char element) {
	int count = 0;
	for (int i = 0; i < array.used; i++) {
		if (array.items[i] == element) count++;
	}
	return count;
}

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


FloatArray Array_slice_float (FloatArray array, int start, int end) {
	if (start < 0 || !(end < array.used)) {
		Array_error(OUT_OF_BOUNDS);
	}
	FloatArray sliced = FloatArray_create(end - start + 1);
	for (int i = 0; i <= sliced.length; i++) {
		sliced.items[i] = array.items[i + start]; 
	}
	sliced.used = sliced.length;
	return sliced;
}


CharArray Array_slice_char (CharArray array, int start, int end) {
	if (start < 0 || !(end < array.length)) {
		Array_error(OUT_OF_BOUNDS);
	}
	CharArray sliced = CharArray_create(end - start + 1);
	for (int i = 0; i <= sliced.length; i++) {
		sliced.items[i] = array.items[i + start]; 
	}
	sliced.used = sliced.length;
	return sliced;
}

IntArray Array_delete_int (IntArray array, int index) {
	if (!(index < array.length) || index < 0) {
		Array_error(OUT_OF_BOUNDS);
		return array;
	}
	int filter (int el, int i, IntArray arr) {
		return i != index;
	}
	array = Array_filter(array, filter);
	return array;
}

FloatArray Array_delete_float (FloatArray array, int index) {
	if (!(index < array.length) || index < 0) {
		Array_error(OUT_OF_BOUNDS);
		return array;
	}
	int filter (float el, int i, FloatArray arr) {
		return i != index;
	}
	array = Array_filter(array, filter);
	return array;
}


CharArray Array_delete_char (CharArray array, int index) {
	if (!(index < array.length) || index < 0) {
		Array_error(OUT_OF_BOUNDS);
		return array;
	}
	int filter (char el, int i, CharArray arr) {
		return i != index;
	}
	array = Array_filter(array, filter);
	return array;
}


IntArray Array_insert_int (IntArray array, int element, int index) {
	if (index < 0) {
		Array_error(OUT_OF_BOUNDS);
		return array;
	}
	IntArray inserted = Array_copy(array);
	if (index > inserted.length - 1) {
		inserted = Array_resize(inserted, index - inserted.length + 1);
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


FloatArray Array_insert_float (FloatArray array, float element, int index) {
	if (index < 0) {
		Array_error(OUT_OF_BOUNDS);
		return array;
	}
	FloatArray inserted = Array_copy(array);
	if (index > inserted.length - 1) {
		inserted = Array_resize(inserted, index - inserted.length + 1);
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


CharArray Array_insert_char (CharArray array, char element, int index) {
	if (index < 0) {
		Array_error(OUT_OF_BOUNDS);
		return array;
	}
	CharArray inserted = Array_copy(array);
	if (index > inserted.length - 1) {
		inserted = Array_resize(inserted, index - inserted.length + 1);
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
FloatArray Array_sort_float (FloatArray array, FloatArraySortFunction function) {
	FloatArray sorted = FloatArray_create(array.length);
	sorted.used = array.used;
	for (int i = 0; i < sorted.length; i++) {
		sorted.items[i] = array.items[i];
	}
	float get (int index) {
		return Array_get_float(sorted, index);
	}
	void set (float element, int index) {
		sorted = Array_set_float(sorted, element, index);	
	}
	void swap (int index1, int index2) {
		float temp = sorted.items[index1];
		sorted.items[index1] = sorted.items[index2];
		sorted.items[index2] = temp;
	}
	function(sorted, get, set, swap);
	return sorted;
}
CharArray Array_sort_char (CharArray array, CharArraySortFunction function) {
	CharArray sorted = CharArray_create(array.length);
	sorted.used = array.used;
	for (int i = 0; i < sorted.length; i++) {
		sorted.items[i] = array.items[i];
	}
	char get (int index) {
		return Array_get_char(sorted, index);
	}
	void set (char element, int index) {
		sorted = Array_set_char(sorted, element, index);
	}
	void swap (int index1, int index2) {
		char temp = sorted.items[index1];
		sorted.items[index1] = sorted.items[index2];
		sorted.items[index2] = temp;
	}
	function(sorted, get, set, swap);
	return sorted;
}

void INT_ARRAY_PRINT (int el, int index, IntArray arr) {
		printf("(%d): %d\n", index, el);
}

void FLOAT_ARRAY_PRINT (float el, int index, FloatArray arr) {
		printf("(%d): %f\n", index, el);
}

void CHAR_ARRAY_PRINT (char el, int index, CharArray arr) {
		printf("(%d): %c\n", index, el);
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


void FLOAT_ARRAY_BUBBLE_SORTER (FloatArray sorted, FloatArrayGetFunction get, FloatArraySetFunction set, ArraySwapFunction swap) {
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

void CHAR_ARRAY_BUBBLE_SORTER (CharArray sorted, CharArrayGetFunction get, CharArraySetFunction set, ArraySwapFunction swap) {
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

void FLOAT_ARRAY_SELECTION_SORTER (FloatArray sorted, FloatArrayGetFunction get, FloatArraySetFunction set, ArraySwapFunction swap) {
	for (int i = 0; i < sorted.used - 1; i++) {
		int min_index = i;
		for (int j = i; j < sorted.used; j++) {
			if (get(j) < get(min_index)) min_index = j;
		}
		if (min_index == i) break;
		swap(i, min_index);
	}
}

void CHAR_ARRAY_SELECTION_SORTER (CharArray sorted, CharArrayGetFunction get, CharArraySetFunction set, ArraySwapFunction swap) {
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

void FLOAT_ARRAY_INSERTION_SORTER (FloatArray sorted, FloatArrayGetFunction get, FloatArraySetFunction set, ArraySwapFunction swap) {
		for (int i = 1; i < sorted.used; i++) {
		int j = i - 1;
		while (j >= 0 && get(j) < get(j - 1)) {
			swap(j, j - 1);
			j--;
		}
	}
}

void CHAR_ARRAY_INSERTION_SORTER (CharArray sorted, CharArrayGetFunction get, CharArraySetFunction set, ArraySwapFunction swap) {
	for (int i = 1; i < sorted.used; i++) {
		int j = i - 1;
		while (j >= 0 && get(j) < get(j - 1)) {
			swap(j, j - 1); 
			j--;
		}
	}
}