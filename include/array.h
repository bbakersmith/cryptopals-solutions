#ifndef _ARRAY_H
#define _ARRAY_H


#include <stdint.h>
#include <stdlib.h>


typedef struct Array {
  size_t length;
  uint8_t *data;
} Array;


Array array_new(size_t length);
void array_free(Array *arr);

Array array_from_string(uint8_t string_data[]);
uint8_t* array_to_string(Array *arr);
void array_print(Array *arr);


#endif
