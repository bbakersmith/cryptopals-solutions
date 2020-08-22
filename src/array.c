#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"


Array array_new(size_t length) {
  Array arr = {
    .length = length,
    .data = (uint8_t *) malloc(length)
  };
  if(arr.data == NULL) {
    perror("malloc");
    exit(1);
  }
  return arr;
}


void array_free(Array *arr) {
  arr->length = 0;
  free(arr->data);
}


Array array_from_data(uint8_t data[], size_t length) {
  Array arr = array_new(length);

  for(size_t i = 0; i < length; i += 1) {
    arr.data[i] = data[i];
  }

  return arr;
}


Array array_from_string(char string_data[]) {
  size_t length = strlen(string_data);
  Array arr = array_new(length);

  for(size_t i = 0; i < length; i += 1) {
    arr.data[i] = (uint8_t) string_data[i];
  }

  return arr;
}


void array_to_string(Array *arr, char result[]) {
  for(size_t i = 0; i < arr->length; i++) {
    result[i] = (char) arr->data[i];
  }
  result[arr->length] = 0;
}


void array_print(Array *arr) {
  for(size_t i = 0; i < arr->length; i++) {
    printf("%c", arr->data[i]);
  }
  printf("\n");
}
