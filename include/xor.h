#ifndef _XOR_H
#define _XOR_H


#include <stdint.h>
#include <stdlib.h>

#include "array.h"


typedef struct XorSingleByteScore {
  size_t id;
  uint32_t score;
  uint8_t key;
} XorSingleByteScore;


void xor_repeating_key(Array *input_arr, Array *key_arr);
int xor_compare_single_byte_scores(const void *a_void, const void *b_void);
void xor_score_single_byte(Array *input_arr, XorSingleByteScore result[], size_t resultlen);


#endif
