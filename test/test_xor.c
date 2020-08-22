#include <stdint.h>
#include <string.h>

#include "unity.h"
#include "unity_fixture.h"

#include "array.h"
#include "hex.h"
#include "xor.h"


TEST_GROUP(xor);


TEST_SETUP(xor) {};
TEST_TEAR_DOWN(xor) {};


TEST(xor, test_xor_repeating_key_decode) {
  char hex_input[512] = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";

  Array input_arr = array_from_string(hex_input);
  hex_decode(&input_arr);

  Array key_arr = array_from_string("ICE");

  xor_repeating_key(&input_arr, &key_arr);
  char result[256];
  array_to_string(&input_arr, result);

  array_free(&input_arr);
  array_free(&key_arr);

  char expected[256] = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";

  TEST_ASSERT_EQUAL_MESSAGE(
    0,
    strcmp(result, expected),
    result
  );
}


TEST(xor, test_xor_repeating_key_encode) {
  char input[256] = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";

  Array input_arr = array_from_string(input);
  Array key_arr = array_from_string("ICE");

  xor_repeating_key(&input_arr, &key_arr);
  hex_encode(&input_arr);

  char result[256];
  array_to_string(&input_arr, result);

  array_free(&input_arr);
  array_free(&key_arr);

  char expected[512] = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";

  TEST_ASSERT_EQUAL_MESSAGE(
    0,
    strcmp(result, expected),
    result
  );
}


TEST(xor, test_hex_to_fixed_xor) {
  Array input_arr = array_from_string("1c0111001f010100061a024b53535009181c");
  hex_decode(&input_arr);

  Array key_arr = array_from_string("686974207468652062756c6c277320657965");
  hex_decode(&key_arr);

  xor_repeating_key(&input_arr, &key_arr);
  hex_encode(&input_arr);

  char result[256];
  array_to_string(&input_arr, result);

  array_free(&input_arr);
  array_free(&key_arr);

  TEST_ASSERT_EQUAL_MESSAGE(
    0,
    strcmp(result, "746865206b696420646f6e277420706c6179"),
    result
  );
}


TEST_GROUP_RUNNER(xor) {
  RUN_TEST_CASE(xor, test_xor_repeating_key_decode);
  RUN_TEST_CASE(xor, test_xor_repeating_key_encode);
  RUN_TEST_CASE(xor, test_hex_to_fixed_xor);
}
