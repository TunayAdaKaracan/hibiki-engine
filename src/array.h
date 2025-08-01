#pragma once
#include <stdint.h>
#include <stdlib.h>

#define RAW_PTR(ptr) (((uint32_t*)ptr)-2)
#define ARRAY_PTR(ptr) ((void *) (ptr + 2))

#define CREATE_ARRAY(T) (T*) array_create(8, sizeof(T))
#define CREATE_ARRAY_WITH_SIZE(T, capacity) (T*) array_create(capacity, sizeof(T))

#define PUSH_ARRAY(ptr, value) PUSH_ARRAY_WITH_SIZE(ptr, value, 8)
#define PUSH_ARRAY_WITH_SIZE(ptr, value, capacity) do { \
    ptr = array_expand(ptr, capacity, sizeof(*(ptr)));\
    ptr[array_length(ptr)-1] = value;\
} while(0)

#define FREE_ARRAY(ptr) free(((uint32_t*)ptr)-2)

// Creates a pointer
// [0] => capacity
// [1] => count
void* array_create(uint32_t capacity, uint32_t size){
    uint32_t *ptr = malloc(2 * sizeof(uint32_t) + capacity * size );
    ptr[0] = capacity;
    ptr[1] = 0;
    return ARRAY_PTR(ptr);
}

void* array_expand(void* array_ptr, uint32_t capacity, uint32_t member_size){
    uint32_t *ptr;
    if(array_ptr == NULL)
        ptr = RAW_PTR(array_create(capacity, member_size));
    else
        ptr = RAW_PTR(array_ptr);

    uint32_t array_capacity = ptr[0];
    uint32_t array_length = ptr[1];
    if(array_length == array_capacity){
        // Need to resize our array
        array_capacity = array_capacity * 2;
        ptr = realloc(ptr, 2 * sizeof(uint32_t) + array_capacity * member_size);
        ptr[0] = array_capacity;
    }
    ptr[1] += 1;
    return ARRAY_PTR(ptr);
}

uint32_t array_length(void* array_ptr){
    return RAW_PTR(array_ptr)[1];
}

uint32_t array_capacity(void* array_ptr){
    return RAW_PTR(array_ptr)[0];
}

#undef ARRAY_PTR
#undef RAW_PTR
