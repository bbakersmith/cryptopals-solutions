#include <stdint.h>

#include "measures.h"
#include "xor.h"


void xor_repeating_key(Array *input_arr, Array *key_arr) {
  size_t keyi = 0;
  for(size_t i = 0; i < input_arr->length; i += 1) {
    input_arr->data[i] = input_arr->data[i] ^ key_arr->data[keyi];
    keyi++;
    if(key_arr->length <= keyi) {
      keyi = 0;
    }
  }
}


int xor_compare_single_byte_scores(const void *a_void, const void *b_void) {
  XorSingleByteScore *a = (XorSingleByteScore *) a_void;
  XorSingleByteScore *b = (XorSingleByteScore *) b_void;
  if(a->score < b->score) {
    return -1;
  } else if(b->score < a->score) {
    return 1;
  } else {
    return 0;
  }
}


void xor_score_single_byte(Array *input_arr, XorSingleByteScore result[], size_t resultlen) {
  XorSingleByteScore scores[256];
  char *xored_string = (char *) malloc(input_arr->length + 1);
  for(uint16_t i = 0; i < 256; i ++) {
    uint8_t c = i;
    Array input_copy = array_copy(input_arr);
    Array key_arr = array_from_data(&c, 1);

    xor_repeating_key(&input_copy, &key_arr);
    array_free(&key_arr);

    array_to_string(&input_copy, xored_string);
    array_free(&input_copy);

    XorSingleByteScore score = {
      .score = total_char_freq_magnitude_difference(xored_string),
      .key = c
    };

    scores[i] = score;
  }
  free(xored_string);

  qsort(scores, 256, sizeof(XorSingleByteScore), &xor_compare_single_byte_scores);

  for(size_t i = 0; i < resultlen; i++) {
    result[i] = scores[i];
  }
}
