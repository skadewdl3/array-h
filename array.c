#include "array.h"

int main () {

	IntArray arr = Array_create_int(10);

	printf("%d\n", arr.length);

	arr = Array_set_int(arr, 1, 0);
	arr = Array_set_int(arr, 2, 1);
	arr = Array_set_int(arr, 3, 2);
	arr = Array_set_int(arr, 10, 10);

	Array_print_int(arr);



	return 0;
}
