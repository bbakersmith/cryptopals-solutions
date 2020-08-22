#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "base64.h"
#include "hex.h"


#define BASE64_PAD_CHAR 61


const uint8_t base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


uint8_t base64_first_of_four(uint8_t c1) {
  return (c1 & 0xFC) >> 2;
}


uint8_t base64_second_of_four(uint8_t c1, uint8_t c2) {
  return ((c1 & 0x3) << 4) + ((c2 & 0xF0) >> 4);
}


uint8_t base64_third_of_four(uint8_t c2, uint8_t c3) {
  return ((c2 & 0xF) << 2) + ((c3 & 0xC0) >> 6);
}


uint8_t base64_fourth_of_four(uint8_t c3) {
  return c3 & 0x3F;
}


void base64_encode(Array *arr) {
  size_t in_i = 0;
  size_t out_i = 0;

  size_t base64len = ceil(arr->length / 3.0) * 4;
  uint8_t *base64_data = (uint8_t *) malloc(base64len);

  // iterate in three byte chunks
  while(1) {
    if(arr->length <= in_i) {
      break;
    }

    uint8_t c1 = arr->data[in_i]; // FIXME invalid read
    in_i++;

    base64_data[out_i] = base64_chars[base64_first_of_four(c1)];
    out_i++;

    if(arr->length <= in_i) {
      base64_data[out_i] = base64_chars[base64_second_of_four(c1, 0)];
      out_i++;
      base64_data[out_i] = BASE64_PAD_CHAR;
      out_i++;
      base64_data[out_i] = BASE64_PAD_CHAR;
      out_i++;
      break;
    }

    uint8_t c2 = arr->data[in_i];
    in_i++;

    base64_data[out_i] = base64_chars[base64_second_of_four(c1, c2)];
    out_i++;

    if(arr->length <= in_i) {
      base64_data[out_i] = base64_chars[base64_third_of_four(c2, 0)];
      out_i++;
      base64_data[out_i] = BASE64_PAD_CHAR;
      out_i++;
      break;
    }

    uint8_t c3 = arr->data[in_i];
    in_i++;

    base64_data[out_i] = base64_chars[base64_third_of_four(c2, c3)];
    out_i++;

    base64_data[out_i] = base64_chars[base64_fourth_of_four(c3)];
    out_i++;
  }

  free(arr->data);
  arr->length = base64len;
  arr->data = base64_data;
}


uint8_t base64_decode_byte(uint8_t c) {
  for(uint8_t i = 0; i < 64; i++) {
    if(c == base64_chars[i]) {
      return i;
    }
  }
  return 0;
}


void base64_decode(Array *arr) {
  size_t resultlen = arr->length / 4 * 3;
  uint8_t *result = (uint8_t *) malloc(resultlen);

  size_t resulti = 0;
  for(size_t datai = 0; datai < arr->length; datai += 4) {
    uint8_t a = base64_decode_byte(arr->data[datai]);
    uint8_t b = base64_decode_byte(arr->data[datai + 1]);
    uint8_t c = base64_decode_byte(arr->data[datai + 2]);
    uint8_t d = base64_decode_byte(arr->data[datai + 3]);

    result[resulti] = (a << 2) + (b >> 4);
    result[resulti + 1] = (b << 4) + (c >> 2);
    result[resulti + 2] = (c << 6) + d;

    resulti += 3;
  }

  free(arr->data);
  arr->length = resultlen;
  arr->data = result;
}


void hex_to_base64(char hex_data[], char result[]) {
  Array arr = array_from_string(hex_data);
  hex_decode(&arr);
  base64_encode(&arr);
  array_to_string(&arr, result);
  array_free(&arr);
}


void string_to_base64(char string_data[], char result[]) {
  Array arr = array_from_string(string_data);
  base64_encode(&arr);
  array_to_string(&arr, result);
  array_free(&arr);
}
