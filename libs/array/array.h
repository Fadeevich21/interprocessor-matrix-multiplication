#ifndef _ARRAY_H
#define _ARRAY_H 1

#include <stdint.h>
#include <stddef.h>

#define MAX_SIZE_ARRAY 16

typedef size_t SizeData;
typedef int32_t ElementData;
typedef ElementData ArrayData[MAX_SIZE_ARRAY];

typedef struct Array {
    SizeData size;
    ArrayData data;
} Array;

Array create_array(const SizeData size);
void init_array(Array* array, const SizeData size);

void read_array(Array* array);
void print_array(const Array array);

Array multiplication_arrays(const Array lhs,
                            const Array rhs);

#endif // _ARRAY_H