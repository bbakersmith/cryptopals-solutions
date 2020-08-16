#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "set1.h"


#define BASE64_PAD_CHAR 61


const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


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


Array string_to_array(uint8_t string_data[]) {
  size_t length = strlen(string_data);
  Array arr = {
    .length = length,
    .data = (uint8_t *) malloc(length)
  };

  for(size_t i = 0; i < length; i += 1) {
    arr.data[i] = string_data[i];
  }

  return arr;
}


Array hex_to_array(uint8_t hex_data[]) {
  size_t length = strlen(hex_data) / 2;
  Array arr = {
    .length = length,
    .data = (uint8_t *) malloc(length)
  };

  for(size_t i = 0; i < length; i += 1) {
    sscanf(&hex_data[i * 2], "%2hhx", &arr.data[i]);
  }

  return arr;
}


uint8_t* array_to_base64(Array string_data) {
  // iterate in three byte chunks
  size_t in_i = 0;
  size_t out_i = 0;
  uint8_t *base64_data = (uint8_t *) malloc(string_data.length * 2); // lazy
  while(true) {
    uint8_t c1;
    uint8_t c2;
    uint8_t c3;

    c1 = string_data.data[in_i];
    if(c1 == 0) {
      break;
    }

    base64_data[out_i] = base64_chars[base64_first_of_four(c1)];
    out_i += 1;

    c2 = string_data.data[in_i + 1];
    base64_data[out_i] = base64_chars[base64_second_of_four(c1, c2)];
    out_i += 1;
    if(c2 == 0) {
      base64_data[out_i] = BASE64_PAD_CHAR;
      out_i += 1;
      base64_data[out_i] = BASE64_PAD_CHAR;
      out_i += 1;
      break;
    }

    c3 = string_data.data[in_i + 2];
    base64_data[out_i] = base64_chars[base64_third_of_four(c2, c3)];
    out_i += 1;
    if(c3 == 0) {
      base64_data[out_i] = BASE64_PAD_CHAR;
      out_i += 1;
      break;
    }

    base64_data[out_i] = base64_chars[base64_fourth_of_four(c3)];
    out_i += 1;
    in_i += 3;
  }

  base64_data[out_i] = 0;
  return base64_data;
}


uint8_t* hex_to_base64(uint8_t hex_data[]) {
  Array hex_arr = hex_to_array(hex_data);
  return array_to_base64(hex_arr);
}


uint8_t* string_to_base64(uint8_t string_data[]) {
  Array string_arr = string_to_array(string_data);
  return array_to_base64(string_arr);
}


uint8_t* array_to_hex(Array hex_data) {
  size_t length = (hex_data.length * 2) + 1;
  uint8_t *result = malloc(length);
  for(size_t i = 0; i < hex_data.length; i++) {
    sprintf(&result[i * 2], "%02x", hex_data.data[i]);
  }
  result[length - 1] = 0;
  return result;
}


Array hex_to_fixed_xor_array(uint8_t hex_data[], uint8_t xor_data[]) {
  Array hex_arr = hex_to_array(hex_data);
  Array xor_arr = hex_to_array(xor_data);

  Array result = {
    .length = hex_arr.length,
    .data = malloc(hex_arr.length)
  };

  for(size_t i = 0; i < hex_arr.length; i += 1) {
    result.data[i] = hex_arr.data[i] ^ xor_arr.data[i];
  }

  return result;
}


uint8_t* hex_to_fixed_xor(uint8_t hex_data[], uint8_t xor_data[]) {
  Array result = hex_to_fixed_xor_array(hex_data, xor_data);
  return array_to_hex(result);
}
