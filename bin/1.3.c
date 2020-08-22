#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "array.h"
#include "hex.h"
#include "set1.h"


void main() {
  uint8_t input[256] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
  Array input_arr = array_from_string(input);
  hex_decode(&input_arr);

  printf("Input: ");
  array_print(&input_arr);

  uint8_t top_char;
  uint32_t top_score = -1;
  for(uint16_t i = 0; i < 26; i ++) {
    uint8_t c = 'A' + i;
    uint8_t *xored_string = single_char_xor(input_arr, c);

    /* printf("C: %c\n", c); */
    /* printf("XORED: %s\n\n", xored_string); */

    uint32_t score = total_char_freq_magnitude_difference(xored_string);

    free(xored_string);

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

  uint8_t *decoded = single_char_xor(input_arr, top_char);
  printf("Decoded: %s\n", decoded);
  free(decoded);
}
