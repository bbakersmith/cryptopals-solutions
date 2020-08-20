#include <stdio.h>
#include <string.h>

#include "array.h"


Array array_new(size_t length) {
  Array arr = {
    .length = length,
    .data = (uint8_t *) malloc(length)
  };
  return arr;
}


void array_free(Array *arr) {
  arr->length = 0;
  free(arr->data);
}


Array array_from_string(uint8_t string_data[]) {
  size_t length = strlen(string_data);
  Array arr = array_new(length);

  for(size_t i = 0; i < length; i += 1) {
    arr.data[i] = string_data[i];
  }

  return arr;
}


uint8_t* array_to_string(Array *arr) {
  uint8_t *result = (uint8_t *) malloc(arr->length + 1);
  for(size_t i = 0; i < arr->length; i++) {
    result[i] = arr->data[i];
  }
  result[arr->length] = 0;
  return result;
}


void array_print(Array *arr) {
  for(size_t i = 0; i < arr->length; i++) {
    printf("%c", arr->data[i]);
  }
  printf("\n");
}
