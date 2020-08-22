#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "array.h"
#include "hex.h"
#include "measures.h"
#include "xor.h"


int main() {
  int bufferlen = 255;
  char input[bufferlen];

  FILE* file = fopen("data/1.4.txt", "r");
  if(file == NULL) {
    perror("fopen");
    exit(1);
  }

  uint8_t top_char;
  uint32_t top_score = -1;
  uint8_t top_decoded[61];

  while(fgets(input, bufferlen, file)) {
    Array input_arr = array_from_string(input);
    hex_decode(&input_arr);

    /* printf("INPUT: %s\n", array_to_string(input_arr)); */

    char *xored_string = (char *) malloc(input_arr.length + 1);
    for(uint16_t i = 0; i < 256; i ++) {
      uint8_t c = i;
      Array input_copy = array_copy(&input_arr);
      Array key_arr = array_from_data(&c, 1);

      xor_repeating_key(&input_copy, &key_arr);
      array_free(&key_arr);

      array_to_string(&input_copy, xored_string);
      array_free(&input_copy);

      uint32_t score = total_char_freq_magnitude_difference(xored_string);

      if(top_score == -1) {
        top_score = score;
        top_char = c;
        size_t zlength = strlen(xored_string);
        for(size_t z = 0; z < zlength + 1; z++) {
          if(z == zlength) {
            top_decoded[z] = 0;
          } else {
            top_decoded[z] = xored_string[z];
          }
        }
      } else if(score < top_score) {
        top_score = score;
        top_char = c;
        size_t zlength = strlen(xored_string);
        for(size_t z = 0; z < zlength + 1; z++) {
          if(z == zlength) {
            top_decoded[z] = 0;
          } else {
            top_decoded[z] = xored_string[z];
          }
        }
      }

    }
    free(xored_string);
    array_free(&input_arr);
  }

  fclose(file);

  printf("Top char: %c\n", top_char);
  printf("Top score: %d\n", top_score);

  printf("Decoded: %s\n", top_decoded);
}
