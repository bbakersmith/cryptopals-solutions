#ifndef _BASE64_H
#define _BASE64_H


#include <stdint.h>

#include "array.h"


uint8_t base64_first_of_four(uint8_t c1);
uint8_t base64_second_of_four(uint8_t c1, uint8_t c2);
uint8_t base64_third_of_four(uint8_t c2, uint8_t c3);
uint8_t base64_fourth_of_four(uint8_t c3);

void base64_encode(Array *string_arr);
void base64_decode(Array *base64_arr);

void hex_to_base64(char hex_data[], char result[]);
void string_to_base64(char string_data[], char result[]);


#endif
