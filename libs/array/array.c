#include "array.h"
#include <stdio.h>
#include <malloc.h>

void init_array(Array* array, const SizeData size) {
    array->size = size;
}

Array create_array(const SizeData size) {
    Array array;
    init_array(&array, size);

    return array;
}

void read_array(Array* array) {
    for (SizeData i = 0; i < array->size; i++) {
        scanf("%d", &(array->data[i]));
    }
}

void print_array(const Array array) {
    for (SizeData i = 0; i < array.size; i++) {
        printf("%d ", array.data[i]);
    }
    printf("\n");
}

Array multiplication_arrays(const Array lhs,
                            const Array rhs) {
    SizeData size = lhs.size; 
    Array array = create_array(size);
    for (SizeData i = 0; i < array.size; i++) {
        array.data[i] = lhs.data[i] * rhs.data[i];
    }

    return array;
}
