#include "../include/allocation.h"
#include <stdlib.h>
#include <stdio.h>

/// Allocates an array of n elements of size member_size in bytes utilizing calloc if the clear flag is set, malloc otherwise.
///	Testing with certain values will show different behavior between calloc and malloc.
/// \param size_t - member size in bytes (can be gotten using the sizeof operator e.g. sizeof(int)
/// \param size_t - number of members in the array
///	\param bool -   1 will clear memory (calling calloc), 0 will not (calling malloc).
/// \return void* - pointer to allocated memory.
void* allocate_array(size_t member_size, size_t nmember,bool clear) {
    if (member_size <= 0 || nmember <= 0) {
        return NULL;
    }
    return clear == true ? (void*)calloc(nmember, member_size) : (void*)malloc(nmember * member_size);
}

/// Realloc
/// - Does not initialize expanded memory
/// - Original contents remain unchanged
/// - If passed a null pointer then a malloc will occur.
/// - May move memory to a new location

/// Simple wrapper around realloc.
/// \param void* - pointer to memory to resize.
/// \param size_t - size of memory to allocate
/// \return void* - pointer to reallocated memory region, may be same as original pointer.
void* reallocate_array(void* ptr, size_t size) {
    if (size <= 0) {
        return NULL;
    }
    return realloc(ptr, size);
}

// Free
// - Should not be called on a null pointer or a pointer not received from allocation.
// - Free does not reinitialize the memory region.
// - An "Invalid Pointer" error may be a sign of bad memory operations or an overflow from a memset, memcpy, or allocation or freeing a pointer twice.
// - If the received pointer is null no operation is performed.

/// Wrapper around free. Frees memory and sets received pointer to NULL.
/// \param void* - pointer to memory to free.
/// \return Nothing
void deallocate_array(void** ptr) {
    if (ptr == NULL) {
        return;
    }
    // realloc(*ptr, 0);
    free(*ptr);
    *ptr = NULL;
    ptr = NULL;
}

/// Takes a file name and reads a line into a newly allocated buffer
/// \param char* - filename to read from
/// \return char* - Pointer to malloced heap space containing buffer
char* read_line_to_buffer(char* filename)
{
    if (filename == NULL) {
        return NULL;
    }
    FILE* file = fopen(filename, "r"); 
    if (file == NULL) {
        return NULL;
    }
    // get file size
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    char* result = (char*)calloc(sizeof(char), file_size);

    char c;
    int i = 0;
    while ((c = fgetc(file)) != EOF) {
        result[i++] = c;
    }
    fclose(file);
    return result;


}
