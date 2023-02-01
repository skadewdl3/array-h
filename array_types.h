// Some colors for better error messages
#define RESET   "\033[0m"			// Reset color to default
#define BLACK   "\033[30m"      	// Black
#define RED     "\033[31m"      	// Red
#define GREEN   "\033[32m"      	// Green
#define YELLOW  "\033[33m"      	// Yellow
#define BLUE    "\033[34m"      	// Blue
#define MAGENTA "\033[35m"      	// Magenta
#define CYAN    "\033[36m"      	// Cyan
#define WHITE   "\033[37m"      	// White

// Enum with Error types
typedef enum {
	OUT_OF_BOUNDS, MEM_ALLOC_FAIL, MEM_REALLOC_FAIL , UNUSED_ACCESS
} ArrayError;

// Function for printing error messages
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
	case UNUSED_ACCESS:
		printf(RED "\nLogical Error: [UNUSED_ACCESS]\n");
		printf(YELLOW "You tried to access an element you haven't used yet. [Array_set] can only modify used elements. Use [Array_insert] to assign a value to this element." RESET);
		break;
	}
}

// Common function used for swapping array elements
typedef void (*ArraySwapFunction) (int, int);


