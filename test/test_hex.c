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
  for(size_t i; i < 4; i += 1) {
    TEST_ASSERT_EQUAL(expected[i], input_arr.data[i]);
  }
}


TEST_GROUP_RUNNER(hex) {
  RUN_TEST_CASE(hex, test_hex_decode);
}
