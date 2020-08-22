#include <string.h>

#include "unity.h"
#include "unity_fixture.h"

#include "hex.h"


TEST_GROUP(hex);


TEST_SETUP(hex) {};
TEST_TEAR_DOWN(hex) {};


TEST(hex, test_hex_decode) {
  Array input_arr = array_from_string("FF00F01C");
  hex_decode(&input_arr);

  TEST_ASSERT_EQUAL(4, input_arr.length);

  uint8_t expected[4] = {255, 0, 240, 28};
  for(size_t i = 0; i < 4; i += 1) {
    TEST_ASSERT_EQUAL(expected[i], input_arr.data[i]);
  }

  array_free(&input_arr);
}


TEST(hex, test_hex_decode_again) {
  Array input_arr = array_from_string("616263");
  hex_decode(&input_arr);

  char result[48];
  array_to_string(&input_arr, result);

  array_free(&input_arr);

  TEST_ASSERT_EQUAL_MESSAGE(0, strcmp(result, "abc"), result);
}


TEST(hex, test_hex_encode) {
  uint8_t data[3] = {255, 0, 28};
  Array input_arr = array_from_data(data, 3);
  hex_encode(&input_arr);

  char result[256];
  array_to_string(&input_arr, result);

  array_free(&input_arr);

  TEST_ASSERT_EQUAL_MESSAGE(0, strcmp(result, "ff001c"), result);
}


TEST(hex, test_hex_encode_again) {
  Array input_arr = array_from_string("abc");
  hex_encode(&input_arr);

  char result[48];
  array_to_string(&input_arr, result);

  array_free(&input_arr);

  TEST_ASSERT_EQUAL_MESSAGE(0, strcmp(result, "616263"), result);
}


TEST_GROUP_RUNNER(hex) {
  RUN_TEST_CASE(hex, test_hex_decode);
  RUN_TEST_CASE(hex, test_hex_decode_again);
  RUN_TEST_CASE(hex, test_hex_encode);
  RUN_TEST_CASE(hex, test_hex_encode_again);
}
