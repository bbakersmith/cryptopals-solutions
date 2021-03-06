#ifndef _MEASURES_H
#define _MEASURES_H


#include <stdint.h>
#include <stdlib.h>

#include "array.h"


uint32_t char_freq(char data[], uint8_t lower_char);
uint32_t magnitude_difference(uint32_t a, uint32_t b);
uint32_t total_char_freq_magnitude_difference(char data[]);
uint32_t hamming_distance(char a[], char b[], size_t length);

typedef struct PredictKeysizeDistance {
  size_t keysize;
  float distance;
} PredictKeysizeDistance;

void predict_keysize(
  Array *data,
  PredictKeysizeDistance result[],
  size_t resultlen
);


#endif
