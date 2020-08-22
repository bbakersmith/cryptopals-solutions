#ifndef _SET1_H
#define _SET1_H


#include <stdint.h>

#include "array.h"


// 1.2


void xor_arrays(Array *target_arr, Array *key_arr);
Array hex_to_fixed_xor_array(char hex_data[], char xor_data[]);
char* hex_to_fixed_xor(char hex_data[], char xor_data[]);


// 1.3


uint32_t char_freq(char data[], uint8_t lower_char);
uint32_t magnitude_difference(uint32_t a, uint32_t b);
uint32_t total_char_freq_magnitude_difference(char data[]);
char* single_char_string(uint8_t c, uint32_t length);
char* single_char_xor(Array arr, uint8_t c);


// 1.5


void encode_repeating_key_xor(char data[], char key[]);
char* encode_hex_string(char data[]);


// 1.6


uint32_t hamming_distance(char a[], char b[], size_t length);
Array decode_base64(Array data);
void decode_repeating_key_xor(char data[], char key[]);


#endif
