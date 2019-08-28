#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/arrays.h"

// LOOK INTO MEMCPY, MEMCMP, FREAD, and FWRITE

// Copy the contents from source array into destination array
// \param src the array the will be copied into the destination array
// \param dst the array that will be copied from the source array
// \param elem_size the number of bytes each array element uses
// \param elem_count the number of elements in the source array
// return true if operation was successful, else false
bool array_copy(const void *src, void *dst, const size_t elem_size, const size_t elem_count) {
	if (src == NULL || dst == NULL) {
		return false;
	}
	if (elem_size <= 0 || elem_count <= 0) {
		return false;
	}
	memcpy(dst, src, elem_count * elem_size);

	return dst != NULL;
}

// Compares if two arrays contain the same contents
// // \param array_a the array that will be compared against array_b
// // \param array_b the array that will be compared against array_a
// // \param elem_size the number of bytes each array element uses in array_a
// // \param elem_count the number of elements in array_a
// // return true if operation was successful, else false
bool array_is_equal(const void *data_one, void *data_two, const size_t elem_size, const size_t elem_count) {
	if (data_one == NULL || data_two == NULL) {
		return false;
	}
	if (elem_size <= 0 || elem_count <= 0) {
		return false;
	}
  	return memcmp(data_one, data_two, elem_size * elem_count) == 0;
}
// Attempts to locate the target from an array
// // \param data the data that may contain the target
// // \param target the target that may be in the data
// // \param elem_size the number of bytes each array element uses and same as the target
// // \param elem_count the number of elements in the data array
// // returns an index to the located target, else return -1 for failure
ssize_t array_locate(const void *data, const void *target, const size_t elem_size, const size_t elem_count) {
	if (data == NULL || target == NULL) {
		return -1;
	}
	if (elem_size <= 0 || elem_count <= 0) {
		return -1;
	}
	for (int i = 0; i < elem_count; i++) {
		if (memcmp(data, target, elem_size) == 0) {
			return i;
		} else {
			data += elem_size;
		}
	}
	return -1;
}

// Writes an array into a binary file
// \param src_data the array the will be wrote into the destination file
// \param dst_file the file that will contain the wrote src_data
// \param elem_size the number of bytes each array element uses
// \param elem_count the number of elements in the source array
// return true if operation was successful, else false
bool array_serialize(const void *src_data, const char *dst_file, const size_t elem_size, const size_t elem_count) {
	if (src_data == NULL || dst_file == NULL) {
		return false;
	}
	if (elem_size <= 0 || elem_count <= 0) {
		return false;
	}
	if (strcmp(dst_file, "") == 0 || strcmp(dst_file, "\n") == 0) {
		return false;
	}
	FILE *fp = fopen(dst_file, "wb");
	if (!fp) {
		return false;
	}
	int count = fwrite(src_data, elem_size, elem_count, fp);

	fclose(fp);
	return count == elem_count;
}

// Reads an array from a binary file
// \param src_file the source file that contains the array to be read into the destination array
// \param dst_data the array that will contain the data stored in the source file
// \param elem_size the number of bytes each array element uses of the destination array
// \param elem_count the number of elements in the destination array
// return true if operation was successful, else false
bool array_deserialize(const char *src_file, void *dst_data, const size_t elem_size, const size_t elem_count) {
	if (src_file == NULL || dst_data == NULL) {
		return false;
	}
	if (strcmp(src_file, "") == 0 || strcmp(src_file, "\n") == 0) {
		return false;
	}
	if (elem_size <= 0 || elem_count <= 0) {
		return false;
	}
	FILE *fp = fopen(src_file, "rb");
	if (!fp) {
		return false;
	}
	int count = fread(dst_data, elem_size, elem_count, fp);
	fclose(fp);
	return count == elem_count;

}
