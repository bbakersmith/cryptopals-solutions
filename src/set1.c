#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "set1.h"


// 1.1


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
  uint8_t *result = array_to_base64(hex_arr);
  free(hex_arr.data);
  return result;
}


uint8_t* string_to_base64(uint8_t string_data[]) {
  Array string_arr = string_to_array(string_data);
  uint8_t *result = array_to_base64(string_arr);
  free(string_arr.data);
  return result;
}


// 1.2


uint8_t* array_to_hex(Array hex_data) {
  size_t length = (hex_data.length * 2) + 1;
  uint8_t *result = (uint8_t *) malloc(length);
  for(size_t i = 0; i < hex_data.length; i++) {
    sprintf(&result[i * 2], "%02x", hex_data.data[i]);
  }
  result[length - 1] = 0;
  return result;
}



Array xor_arrays(Array a, Array b) {
  Array result = {
    .length = a.length,
    .data = (uint8_t *) malloc(a.length)
  };

  for(size_t i = 0; i < a.length; i += 1) {
    result.data[i] = a.data[i] ^ b.data[i];
  }

  return result;
}


Array hex_to_fixed_xor_array(uint8_t hex_data[], uint8_t xor_data[]) {
  Array hex_arr = hex_to_array(hex_data);
  Array xor_arr = hex_to_array(xor_data);
  Array result = xor_arrays(hex_arr, xor_arr);
  free(hex_arr.data);
  free(xor_arr.data);
  return result;
}


uint8_t* hex_to_fixed_xor(uint8_t hex_data[], uint8_t xor_data[]) {
  Array xored_arr = hex_to_fixed_xor_array(hex_data, xor_data);
  uint8_t *result =  array_to_hex(xored_arr);
  free(xored_arr.data);
  return result;
}


// 1.3


// https://en.wikipedia.org/wiki/Letter_frequency
const uint32_t english_char_freq[26] = {
  8497, // a
  1492, // b
  2202, // ...
  4253,
  11162,
  2228,
  2015,
  6094,
  7546,
  153,
  1292,
  4025,
  2406,
  6749,
  7507,
  1929,
  95,
  7587,
  6327,
  9356,
  2758,
  978,
  2560,
  150,
  1994,
  77
};


const uint32_t english_first_char_freq[26] = {
  1682,
  4434,
  5238,
  3174,
  2799,
  4027,
  1642,
  4200,
  7294,
  511,
  856,
  2415,
  3826,
  2284,
  7631,
  4319,
  222,
  2826,
  6686,
  15978,
  1183,
  824,
  5497,
  45,
  763,
  45
};


uint32_t char_freq(uint8_t data[], uint8_t lower_char) {
  size_t length = strlen(data); // FIXME this is segfaulting
  size_t count = 0;
  size_t non_whitespace_count = 0;
  for(size_t i = 0; i < length; i++) {
    uint8_t c = data[i];
    if(c == lower_char || c == (lower_char - 32)) {
      count += 1;
    }
    if(c != ' ' && c != '\n' && c != '\t') {
      non_whitespace_count++;
    }
  }

  uint32_t freq = ((count * 1.0) / non_whitespace_count) * 100000;
  return freq;
}


uint32_t magnitude_difference(uint32_t a, uint32_t b) {
  uint32_t result;
  if(a < b) {
    if(a == 0) {
      result = b;
    } else {
      result = b / a;
    }
  } else {
    if(b == 0) {
      result = a;
    } else {
      result = a / b;
    }
  }
  return result;
}


uint32_t total_char_freq_magnitude_difference(uint8_t *data) {
  uint32_t result = 0;
  for(uint8_t i = 0; i < 26; i++) {
    uint8_t c = 'a' + i;
    uint32_t freq = char_freq(data, c);
    result += magnitude_difference(freq, english_char_freq[i]);
  }
  return result;
}


uint8_t* single_char_string(uint8_t c, uint32_t length) {
  uint8_t *result = (uint8_t *) malloc(length + 1);
  for(uint32_t i = 0; i < length; i++) {
    result[i] = c;
  }
  result[length + 1] = 0;
  return result;
}


uint8_t* array_to_string(Array arr) {
  size_t length = arr.length + 1;
  uint8_t *result = (uint8_t *) malloc(length);
  for(size_t i = 0; i < arr.length; i++) {
    result[i] = arr.data[i];
  }
  result[arr.length] = 0;
  return result;
}


uint8_t* single_char_xor(Array arr, uint8_t c) {
  Array result = {
    .length = arr.length,
    .data = (uint8_t *) malloc(arr.length)
  };

  for(size_t i = 0; i < arr.length; i++) {
    result.data[i] = arr.data[i] ^ c;
  }

  uint8_t *result_string = array_to_string(result);
  free(result.data);
  return result_string;
}


uint8_t* decode_hex_string(uint8_t hex_data[]) {
  size_t length = strlen(hex_data) / 2;
  uint8_t *result = (uint8_t *) malloc(length + 1);
  for(size_t i = 0; i < length; i += 1) {
    sscanf(&hex_data[i * 2], "%2hhx", &result[i]);
  }
  result[length] = 0;
  return result;
}


void encode_repeating_key_xor(uint8_t data[], uint8_t key[]) {
  size_t datalen = strlen(data);
  size_t keylen = strlen(key);

  size_t keyi = 0;
  for(size_t datai = 0; datai < datalen; datai++) {
    /* printf("%c ^ %c ", data[datai], key[keyi]); */

    data[datai] = data[datai] ^ key[keyi];

    /* printf("= %c(%d, %02x)\n", data[datai], data[datai], data[datai]); */

    keyi++;
    if(keylen <= keyi) {
      keyi = 0;
    }
  }
}


uint8_t *encode_hex_string(uint8_t data[]) {
  size_t datalen = strlen(data);
  size_t resultlen = (datalen * 2) + 1;
  uint8_t *result = (uint8_t *) malloc(resultlen);

  for(size_t i = 0; i < datalen; i++) {
    sprintf(&result[i * 2], "%02x", data[i]);
  }

  result[resultlen - 1] = 0;
  return result;
}
