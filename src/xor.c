#include <stdint.h>

#include "xor.h"


void xor_repeating_key(Array *target_arr, Array *key_arr) {
  size_t keyi = 0;
  for(size_t i = 0; i < target_arr->length; i += 1) {
    target_arr->data[i] = target_arr->data[i] ^ key_arr->data[keyi];
    keyi++;
    if(key_arr->length <= keyi) {
      keyi = 0;
    }
  }
}
