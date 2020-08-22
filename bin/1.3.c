#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "array.h"
#include "hex.h"
#include "measures.h"
#include "xor.h"


int main() {
  char input[256] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
  Array input_arr = array_from_string(input);
  hex_decode(&input_arr);

  printf("Input: ");
  array_print(&input_arr);

  uint8_t top_char;
  uint32_t top_score = -1;
  char xored_string[256];
  for(uint16_t i = 0; i < 26; i ++) {
    Array input_copy = array_copy(&input_arr);

    uint8_t c = 'A' + i;
    Array key_arr = array_from_data(&c, 1);

    xor_repeating_key(&input_copy, &key_arr);
    array_free(&key_arr);

    array_to_string(&input_copy, xored_string);
    array_free(&input_copy);

    /* printf("C: %c\n", c); */
    /* printf("XORED: %s\n\n", xored_string); */

    uint32_t score = total_char_freq_magnitude_difference(xored_string);

    if(top_score == -1) {
      top_score = score;
      top_char = c;
    } else if(score < top_score) {
      top_score = score;
      top_char = c;
    }
  }

  printf("Top char: %c\n", top_char);
  printf("Top score: %d\n", top_score);

  Array key_arr = array_from_data(&top_char, 1);
  xor_repeating_key(&input_arr, &key_arr);
  array_free(&key_arr);

  array_to_string(&input_arr, xored_string);
  array_free(&input_arr);

  printf("Decoded: %s\n", xored_string);
}
