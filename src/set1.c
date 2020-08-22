#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base64.h"
#include "hex.h"
#include "set1.h"
#include "xor.h"


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


uint32_t char_freq(char data[], uint8_t lower_char) {
  size_t length = strlen(data);
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


uint32_t total_char_freq_magnitude_difference(char data[]) {
  uint32_t result = 0;
  for(uint8_t i = 0; i < 26; i++) {
    uint8_t c = 'a' + i;
    uint32_t freq = char_freq(data, c);
    result += magnitude_difference(freq, english_char_freq[i]);
  }
  return result;
}


// 1.6


uint32_t hamming_distance(char a[], char b[], size_t length) {
  uint32_t distance = 0;
  for(size_t c = 0; c < length; c++) {
    for(uint8_t i = 0; i < 8; i++) {
      if((a[c] ^ b[c]) & (1 << i)) {
        distance += 1;
      }
    }
  }
  return distance;
}
