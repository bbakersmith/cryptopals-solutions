#include <stdio.h>

#include "hex.h"


void hex_decode(Array *arr) {
  char *hex_string = (char *) malloc(arr->length + 1);
  if(hex_string == NULL) {
    perror("malloc");
    exit(1);
  }
  array_to_string(arr, hex_string);

  size_t resultlen = arr->length / 2;
  char *result = (char *) malloc(resultlen);
  if(result == NULL) {
    perror("malloc");
    exit(1);
  }

  for(size_t i = 0; i < resultlen; i++) {
    sscanf(&hex_string[i * 2], "%2hhx", &result[i]);
  }

  free(hex_string);
  free(arr->data);
  arr->length = resultlen;
  arr->data = (uint8_t *) result;
}


void hex_encode(Array *arr) {
  size_t resultlen = arr->length * 2;
  char *result = (char *) malloc(resultlen);
  if(result == NULL) {
    perror("malloc");
    exit(1);
  }

  for(size_t i = 0; i < arr->length; i++) {
    char hex[3];
    sprintf(hex, "%02x", arr->data[i]);
    size_t resulti = i * 2;
    result[resulti] = hex[0];
    result[resulti + 1] = hex[1];
  }

  free(arr->data);
  arr->length = resultlen;
  arr->data = (uint8_t *) result;
}
