#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "array.h"
#include "base64.h"
#include "measures.h"
#include "xor.h"


uint8_t* get_transposed_block(FILE *file, uint8_t keysize, uint8_t i) {
  fseek(file, 0, SEEK_END);
  int filesize = ftell(file);

  uint8_t *result = (uint8_t *) malloc(((int) (filesize / keysize)) + 1);
  uint8_t *buffer = (uint8_t *) malloc(keysize + 1);

  size_t resulti = 0;
  while(true) {
    rewind(file);
    uint8_t num_read = fread(buffer, 1, keysize, file);
    result[resulti] = buffer[i];
    resulti++;

    if(num_read < keysize) {
      result[resulti] = 0;
      break;
    }
  }

  free(buffer);
  return result;
}


int main() {
  FILE *file = fopen("data/1.6.txt", "r");

  fseek(file, 0, SEEK_END);
  int filesize = ftell(file);
  rewind(file);

  Array data = array_new(filesize);
  fread(data.data, 1, filesize, file);
  fclose(file);

  array_remove_value(&data, '\n');
  base64_decode(&data);

  // get the top n predicted keysizes
  size_t keysizeslen = 1;
  PredictKeysizeDistance keysizes[keysizeslen];
  predict_keysize(&data, keysizes, keysizeslen);

  for(size_t i = 0; i < keysizeslen; i++) {
    printf(
      "Predicted key size %lu: %lu (%f)\n",
      i,
      keysizes[i].keysize,
      keysizes[i].distance
    );
  }

  // get the top n predicted keys for each predicted keysize
  for(size_t i = 0; i < keysizeslen; i++) {
    size_t keysize = keysizes[i].keysize;
    Array key_arr = array_new(keysize);

    for(uint8_t keyi = 0; keyi < keysize; keyi++) {
      size_t blocklen = ((size_t) (data.length / keysize)) + 1;

      Array block = array_new(blocklen);

      size_t blocki = 0;
      for(size_t datai = keyi; datai < data.length; datai += keysize) {
        block.data[blocki] = data.data[datai];
        blocki++;
      }

      // TODO make it possible to try top n key chars
      XorSingleByteScore top_score;
      xor_score_single_byte(&block, &top_score, 1);
      key_arr.data[keyi] = top_score.key;

      array_free(&block);
    }

    Array data_copy = array_copy(&data);
    xor_repeating_key(&data_copy, &key_arr);

    printf("\n\n\n-------------------------\n");
    printf("Keysize: %lu, ", key_arr.length);
    printf("Key: ");
    array_print(&key_arr);
    printf("\n-------------------------\n");
    array_print(&data_copy);

    array_free(&data_copy);
    array_free(&key_arr);

    // could make this better by
    // - scoring decoded results of all keysizes
    // - storing those results and sorting them
    // - printing so they show up in order from best score to worst
  }

  array_free(&data);

  return 0;
}
