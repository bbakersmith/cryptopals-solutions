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

Array array_from_data(uint8_t data[], size_t length);
Array array_from_string(char string_data[]);
void array_to_string(Array *arr, char result[]);
void array_print(Array *arr);
Array array_copy(Array *arr);
void array_remove_value(Array *arr, uint8_t value);


#endif
