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

// Array Function Types
typedef void (*IntArrayFunction) (int, int);
typedef void (*FloatArrayFunction)(float, int);
typedef void (*CharArrayFunction)(char, int);


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
	IntArray: Array_push_concat_arr_int,							\
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

void Array_destroy_int (IntArray array) {
	free(array.arr);
}
void Array_destroy_float (FloatArray array) {
	free(array.arr);
}
void Array_destroy_char (CharArray array) {
	free(array.arr);
}

void Array_foreach_int (IntArray array, IntArrayFunction function) {
	for (int i = 0; i < array.length; i++) {
		function(array.arr[i], i);
	}
}
void Array_foreach_float (FloatArray array, FloatArrayFunction function) {
	for (int i = 0; i < array.length; i++) {
		function(array.arr[i], i);
	}
}
void Array_foreach_char (CharArray array, CharArrayFunction function) {
	for (int i = 0; i < array.length; i++) {
		function(array.arr[i], i);
	}
}

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

