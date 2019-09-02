#include "../include/bitmap.h"
#include <math.h>

#define NUM_BYTE 8.0
// data is an array of uint8_t and needs to be allocated in bitmap_create
//      and used in the remaining bitmap functions. You will use data for any bit operations and bit logic
// bit_count the number of requested bits, set in bitmap_create from n_bits
// byte_count the total number of bytes the data contains, set in bitmap_create

/*
typedef struct bitmap {
    uint8_t *data;
    size_t bit_count, byte_count;
} bitmap_t;
*/

/// Creates a bitmap to contain 'n' bits (zero initialized)
/// \param n_bits
/// \return New bitmap pointer, NULL on error
bitmap_t *bitmap_create(size_t n_bits) {
    if (n_bits <= 0) {
        return NULL;
    }
    bitmap_t* map = (bitmap_t*)malloc(sizeof(bitmap_t));
    map->bit_count = n_bits; 
    map->byte_count = ceil(n_bits / NUM_BYTE);
    map->data = (uint8_t*)calloc(map->byte_count, sizeof(uint8_t));
    return map;
}

/// Sets the requested bit in bitmap
/// \param bitmap The bitmap
/// \param bit The bit to set
bool bitmap_set(bitmap_t *const bitmap, const size_t bit) {
	if (bitmap == NULL || bit < 0) {
        return false;
    }
    if (bitmap->bit_count < bit) {
        return false;
    }
    int i = bit / sizeof(size_t);
    int pos = bit % sizeof(size_t);

    unsigned int flag = 1;
    flag = flag << pos; 
    bitmap->data[i] = bitmap->data[i] | flag; 

    // bitmap->data[bit/sizeof(size_t)] |= 1 << (bit%sizeof(size_t))

    return true;
}

/// Clears requested bit in bitmap
/// \param bitmap The bitmap
/// \param bit The bit to be cleared
bool bitmap_reset(bitmap_t *const bitmap, const size_t bit) {
    if (bitmap == NULL || bit < 0) {
        return false;
    }
    if (bitmap->bit_count < bit) {
        return false;
    }
    bitmap->data[bit/sizeof(size_t)] &= ~(1 << (bit%sizeof(size_t)));

    return true;
}


/// Returns bit in bitmap
/// \param bitmap The bitmap
/// \param bit The bit to queried
/// \return State of requested bit
bool bitmap_test(const bitmap_t *const bitmap, const size_t bit) {
    if (bitmap == NULL || bit < 0) {
        return false;
    }
    if (bitmap->bit_count < bit) {
        return false;
    }
    return (bitmap->data[bit/sizeof(size_t)] & (1 << (bit%sizeof(size_t)))) != 0 ? true : false;
}

/// Find the first set bit
/// \param bitmap The bitmap
/// \return The first one bit address, SIZE_MAX on error/Not found
size_t bitmap_ffs(const bitmap_t *const bitmap) {
    if (bitmap == NULL) {
        return SIZE_MAX;
    }
    int i;
    for (i = 0; i < bitmap->bit_count; i++) {
        if (bitmap_test(bitmap, i)) {
            return i;
        }
    }
    return SIZE_MAX;

}

/// Find first zero bit
/// \param bitmap The bitmap
/// \return The first zero bit address, SIZE_MAX on error/Not found
size_t bitmap_ffz(const bitmap_t *const bitmap) {
    if (bitmap == NULL) {
        return SIZE_MAX;
    }
    int i;
    for (i = 0; i < bitmap->bit_count; i++) {
        if (!bitmap_test(bitmap, i)) {
            return i;
        }
    }
    return SIZE_MAX;

}

/// Destructs and destroys bitmap object
/// \param bit The bitmap
/// \return The Success or Failure of destruct and destroy bitmap object
bool bitmap_destroy(bitmap_t *bitmap) {
    if (bitmap == NULL) {
        return false;
    }
    free(bitmap->data);
    free(bitmap);
    return true;
}
