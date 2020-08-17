#ifndef _SET1_H
#define _SET1_H


#include <stdint.h>
#include <stdint.h>


typedef struct Array {
  size_t length;
  uint8_t *data;
} Array;


// 1.1


uint8_t base64_first_of_four(uint8_t c1);
uint8_t base64_second_of_four(uint8_t c1, uint8_t c2);
uint8_t base64_third_of_four(uint8_t c2, uint8_t c3);
uint8_t base64_fourth_of_four(uint8_t c3);
Array string_to_array(uint8_t string_data[]);
Array hex_to_array(uint8_t hex_data[]);
uint8_t* array_to_base64(Array string_data);
uint8_t* hex_to_base64(uint8_t hex_data[]);
uint8_t* string_to_base64(uint8_t string_data[]);


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
uint8_t* array_to_string(Array arr);
uint8_t* single_char_xor(Array arr, uint8_t c);
uint8_t* decode_hex_string(uint8_t hex_data[]);


#endif