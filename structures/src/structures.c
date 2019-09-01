#include "../include/structures.h"
#include <stdio.h>
#include <memory.h>

// Purpose: Compares two SAMPLE structs member-by-member
// Receives: struct_a - first struct to compare
//			 struct_b - second struct to compare
// Returns: 1 if the structs match, 0 otherwise.
int compare_structs(sample_t* a, sample_t* b) {
	if (a == NULL || b == NULL) {
		return 0;
	}
	if (a->a != b->a) {
		return 0;
	}
	if (a->b != b->b) {
		return 0;
	}
	if (a->c != b->c) {
		return 0;
	}
	return 1;
}

// Purpose: Simple function to show the alignment of different variables on standard output.
// Receives: Nothing
// Returns: Nothing
void print_alignments() {
	printf("Alignment of int is %zu bytes\n",__alignof__(int));
	printf("Alignment of double is %zu bytes\n",__alignof__(double));
	printf("Alignment of float is %zu bytes\n",__alignof__(float));
	printf("Alignment of char is %zu bytes\n",__alignof__(char));
	printf("Alignment of long long is %zu bytes\n",__alignof__(long long));
	printf("Alignment of short is %zu bytes\n",__alignof__(short));
	printf("Alignment of structs are %zu bytes\n",__alignof__(fruit_t));
}

// Purpose: Initializes an orange_t struct
// Receives: orange_t* - pointer to an orange_t struct
// Returns: -1 if there was an error, 0 otherwise.
int initialize_orange(orange_t* a) {
	if (a == NULL) {
		return -1;
	}
	memset(a, 0, sizeof(orange_t));
	a->type = ORANGE;
	return 0;
}

// Purpose: Initializes an apple_t struct
// Receives: apple_t* - pointer to an apple_t struct
// Returns: -1 if there was an error, 0 otherwise.
int initialize_apple(apple_t* a) {
	if (a == NULL) {
		return -1;
	}
	memset(a, 0, sizeof(apple_t));
	a->type = APPLE;
	return 0;
}

// Purpose: Initializes an array of fruits with the specified number of apples and oranges
// Receives: fruit_t* a - pointer to an array of fruits
//						int apples - the number of apples
//						int oranges - the number of oranges
// Returns: -1 if there was an error, 0 otherwise.
int initialize_array(fruit_t* a, int apples, int oranges) {
	if (a == NULL || apples < 0 || oranges < 0) {
		return -1;
	}
	fruit_t* pFruit = a;
	for (int i = 0; i < apples; i++) {
		initialize_apple((apple_t*)pFruit++);
	}
	for (int j = 0; j < oranges; j++) {
		initialize_orange((orange_t*)pFruit++);
	}
	return 0;
}

// Purpose: Categorizes fruits into apples and oranges
// Receives:  fruit_t* a - pointer to an array of fruits,
//			  int* apples - pointer to apples pass-back address,
//			  int* oranges - pointer to oranges pass-back address,
//			  const size_t size - size of array
// Returns: The size of the array, -1 if there was an error.
int sort_fruit(const fruit_t* a, int* apples,int* oranges, const size_t size) {
	if (a == NULL || apples == NULL || oranges == NULL) {
		return -1;
	}
	if (size == 0) {
		return -1;
	}

	for(size_t i = 0; i < size; i++) {
		if (IS_APPLE(a)) {
			(*apples) += 1;
		} else if (IS_ORANGE(a)) {
			(*oranges) += 1;
		} else {
			return -1;
		}
		a += 1;
	}

	if (*apples + *oranges != (int)size) {
		return -1;
	}
	return (int)size;
}