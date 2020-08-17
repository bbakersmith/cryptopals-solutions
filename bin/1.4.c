#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "set1.h"


void main() {
  FILE* filePointer;
  int bufferLength = 255;
  char input[bufferLength];

  filePointer = fopen("data/1.4.txt", "r");

  uint8_t top_char;
  uint32_t top_score = -1;
  uint8_t top_decoded[61];

  while(fgets(input, bufferLength, filePointer)) {
    Array input_arr = hex_to_array(input);

    /* printf("INPUT: %s\n", array_to_string(input_arr)); */

    for(uint16_t i = 0; i < 256; i ++) {
      uint8_t c = i;
      uint8_t *xored_string = single_char_xor(input_arr, c);

      /* printf("C: %c\n", c); */
      /* printf("XORED: %s\n\n", xored_string); */

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

      free(xored_string);
    }
  }

  fclose(filePointer);

  printf("Top char: %c\n", top_char);
  printf("Top score: %d\n", top_score);

  printf("Decoded: %s\n", top_decoded);
}
