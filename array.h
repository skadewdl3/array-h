#include <stdio.h>

#include "array_types.h"
#include "array_int.h"
#include "array_float.h"
#include "array_char.h"
#include "array_string.h"

// done
#define Array_resize(array, function) _Generic((array),					\
	IntArray: Array_resize_int,											\
	FloatArray: Array_resize_float,										\
	CharArray: Array_resize_char,										\
	StringArray: Array_resize_string									\
)(array, function);
// done

#define Array_foreach(array, function) _Generic((array),				\
	IntArray: Array_foreach_int,										\
	FloatArray: Array_foreach_float,									\
	CharArray: Array_foreach_char,										\
	StringArray: Array_foreach_string									\
)(array, function);

// done
#define Array_filter(array, function) _Generic((array),					\
	IntArray: Array_filter_int,											\
	FloatArray: Array_filter_float,										\
	CharArray: Array_filter_char										\
)(array, function);
// done

#define Array_destroy(array) _Generic((array),							\
	IntArray: Array_destroy_int,										\
	FloatArray: Array_destroy_float,									\
	CharArray: Array_destroy_char,										\
	StringArray: Array_destroy_string									\
)(array);

// done
#define Array_push(array, element) _Generic((array),					\
	IntArray: Array_push_int,											\
	FloatArray: Array_push_float,										\
	CharArray: Array_push_char,											\
	StringArray: Array_push_string										\
)(array, element);

// done

#define Array_unshift(array, element) _Generic((array),					\
	IntArray: Array_unshift_int,										\
	FloatArray: Array_unshift_float,									\
	CharArray: Array_unshift_char,										\
	StringArray: Array_unshift_string									\
)(array, element);

#define Array_concat(array, elements, length) _Generic((elements),		\
	IntArray: Array_concat_arr_int,										\
	FloatArray: Array_concat_arr_float,									\
	CharArray: Array_concat_arr_char,									\
	int*: Array_concat_int,												\
	float*: Array_concat_float,											\
	char*: Array_concat_char											\
)(array, elements, length);
// done

#define Array_from(elements, length) _Generic((elements),				\
	int*: Array_from_int,												\
	float*: Array_from_float,											\
	char*: Array_from_char,												\
	char**: Array_from_string											\
)(elements, length);

// done
#define Array_copy(elements) _Generic((elements),						\
	IntArray: Array_copy_int,											\
	FloatArray: Array_copy_float,										\
	CharArray: Array_copy_char											\
)(elements);

#define Array_sort(array, sorter) _Generic((array),						\
	IntArray: Array_sort_int,											\
	FloatArray: Array_sort_float,										\
	CharArray: Array_sort_char											\
)(array, sorter);

// done
#define Array_get(array, index) _Generic((array),						\
	IntArray: Array_get_int,											\
	FloatArray: Array_get_float,										\
	CharArray: Array_get_char,											\
	StringArray: Array_get_string										\
)(array, index);

// done

#define Array_set(array, element, index) _Generic((array),				\
	IntArray: Array_set_int,											\
	FloatArray: Array_set_float,										\
	CharArray: Array_set_char,											\
	StringArray: Array_set_string										\
)(array, element, index);

// done
#define Array_exists(array, element) _Generic((array),					\
	IntArray: Array_exists_int,											\
	FloatArray: Array_exists_float,										\
	CharArray: Array_exists_char										\
)(array, element);

// done
#define Array_count(array, element) _Generic((array),					\
	IntArray: Array_count_int,											\
	FloatArray: Array_count_float,										\
	CharArray: Array_count_char											\
)(array, element);

// done
#define Array_slice(array, start, end) _Generic((array),				\
	IntArray: Array_slice_int,											\
	FloatArray: Array_slice_float,										\
	CharArray: Array_slice_char,										\
	StringArray: Array_slice_string										\
)(array, start, end);

#define Array_map(array, map) _Generic((array),							\
	IntArray: Array_map_int,											\
	FloatArray: Array_map_float,										\
	CharArray: Array_map_char											\
)(array, map);

// done
#define Array_pop(array) _Generic((array),								\
	IntArray: Array_pop_int,											\
	FloatArray: Array_pop_float,										\
	CharArray: Array_pop_char,											\
	StringArray: Array_pop_string										\
)(array);
// done

#define Array_delete(array, index) _Generic((array),					\
	IntArray: Array_delete_int,											\
	FloatArray: Array_delete_float,										\
	CharArray: Array_delete_char										\
)(array, index);

// done

#define Array_insert(array, element, index) _Generic((array),			\
	IntArray: Array_insert_int,											\
	FloatArray: Array_insert_float,										\
	CharArray: Array_insert_char										\
)(array, element, index);

