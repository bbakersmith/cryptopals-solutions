#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "array.h"
#include "hex.h"
#include "measures.h"
#include "xor.h"


int main() {
  FILE* file = fopen("data/1.4.txt", "r");
  if(file == NULL) {
    perror("fopen");
    exit(1);
  }

  int bufferlen = 255;
  char input[bufferlen];

  size_t rowcount = 0;
  while(fgets(input, bufferlen, file)) {
    rowcount++;
  }
  rewind(file);

  XorSingleByteScore top_score_per_row[rowcount];

  for(size_t row = 0; row < rowcount; row++) {
    size_t row_start_position = ftell(file);
    fgets(input, bufferlen, file);

    Array input_arr = array_from_string(input);
    hex_decode(&input_arr);

    XorSingleByteScore top_score;
    xor_score_single_byte(&input_arr, &top_score, 1);
    array_free(&input_arr);

    top_score.id = row_start_position;

    top_score_per_row[row] = top_score;
  }

  qsort(top_score_per_row, rowcount, sizeof(XorSingleByteScore), &xor_compare_single_byte_scores);

  printf("Top char: %c\n", top_score_per_row[0].key); // should be '5'
  printf("Top score: %d\n", top_score_per_row[0].score); // should be 16840

  fseek(file, top_score_per_row[0].id, SEEK_SET);
  if(fgets(input, bufferlen, file) == NULL) {
    perror("fgets");
    exit(1);
  }

  Array input_arr = array_from_string(input);
  hex_decode(&input_arr);

  Array key_arr = array_from_data(&top_score_per_row[0].key, 1);
  xor_repeating_key(&input_arr, &key_arr);
  array_free(&key_arr);

  char decoded[bufferlen];
  array_to_string(&input_arr, decoded);
  array_free(&input_arr);

  printf("Decoded: %s\n", decoded);

  fclose(file);
}
