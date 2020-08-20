#ifndef _SET1_H
#define _SET1_H


#include <stdint.h>

#include "array.h"


// 1.2


Array xor_arrays(Array a, Array b);
uint8_t* array_to_hex(Array hex_data);
Array hex_to_fixed_xor_array(uint8_t hex_data[], uint8_t xor_data[]);
uint8_t* hex_to_fixed_xor(uint8_t hex_data[], uint8_t xor_data[]);


// 1.3


uint32_t char_freq(uint8_t *data, uint8_t lower_char);
uint32_t magnitude_difference(uint32_t a, uint32_t b);
uint32_t total_char_freq_magnitude_difference(uint8_t data[]);
uint8_t* single_char_string(uint8_t c, uint32_t length);
uint8_t* single_char_xor(Array arr, uint8_t c);
uint8_t* decode_hex_string(uint8_t hex_data[]);


// 1.5


void encode_repeating_key_xor(uint8_t data[], uint8_t key[]);
uint8_t *encode_hex_string(uint8_t data[]);


// 1.6


uint32_t hamming_distance(uint8_t a[], uint8_t b[], size_t length);
Array decode_base64(Array data);
void decode_repeating_key_xor(uint8_t data[], uint8_t key[]);


#endif
