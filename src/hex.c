#include <stdio.h>

#include "hex.h"


void hex_decode(Array *hex_arr) {
  size_t resultlen = hex_arr->length / 2;
  uint8_t *result = (uint8_t *) malloc(resultlen);

  for(size_t i = 0; i < resultlen; i += 1) {
    sscanf(&hex_arr->data[i * 2], "%2hhx", &result[i]);
  }

  free(hex_arr->data);
  hex_arr->length = resultlen;
  hex_arr->data = result;
}
