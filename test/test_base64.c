#include <string.h>

#include "unity.h"
#include "unity_fixture.h"

#include "array.h"
#include "base64.h"


TEST_GROUP(base64);


TEST_SETUP(base64) {};
TEST_TEAR_DOWN(base64) {};


TEST(base64, test_base64_first_of_four) {
  TEST_ASSERT_EQUAL(0, base64_first_of_four(0));
  TEST_ASSERT_EQUAL(63, base64_first_of_four(255));
  TEST_ASSERT_EQUAL(24, base64_first_of_four(97));
}


TEST(base64, test_base64_second_of_four) {
  TEST_ASSERT_EQUAL(0, base64_second_of_four(0, 0));
  TEST_ASSERT_EQUAL(63, base64_second_of_four(255, 255));
  TEST_ASSERT_EQUAL(22, base64_second_of_four(97, 98));
}


TEST(base64, test_base64_third_of_four) {
  TEST_ASSERT_EQUAL(0, base64_third_of_four(0, 0));
  TEST_ASSERT_EQUAL(63, base64_third_of_four(255, 255));
  TEST_ASSERT_EQUAL(9, base64_third_of_four(98, 99));
}


TEST(base64, test_base64_fourth_of_four) {
  TEST_ASSERT_EQUAL(0, base64_fourth_of_four(0));
  TEST_ASSERT_EQUAL(63, base64_fourth_of_four(255));
  TEST_ASSERT_EQUAL(35, base64_fourth_of_four(99));
}


TEST(base64, test_base64_encode) {
  typedef struct Case {
    uint8_t input[4];
    uint8_t expected[5];
  } Case;

  Case cases[3] = {
    {"abc", "YWJj"},
    {"ab", "YWI="},
    {"a", "YQ=="}
  };

  char msg[50];
  for(uint8_t i = 0; i < 3; i++) {
    Array arr = array_from_string(cases[i].input);
    base64_encode(&arr);
    uint8_t *result = array_to_string(&arr);
    array_free(&arr);

    sprintf(msg, "Failed iteration %i with %s", i, result);
    TEST_ASSERT_EQUAL_MESSAGE(0, strcmp(result, cases[i].expected), msg);
  }
}


TEST(base64, test_base64_decode) {
  Array input = array_from_string("Zm9vIGJhciBiYXo=");
  base64_decode(&input);
  uint8_t *result_string = array_to_string(&input);
  TEST_ASSERT_EQUAL_MESSAGE(
    0,
    strcmp(result_string, "foo bar baz"),
    result_string
  );
}


TEST(base64, test_string_to_base64) {
  uint8_t *base64_data = string_to_base64("abc123X");
  TEST_ASSERT_EQUAL_MESSAGE(0, strcmp(base64_data, "YWJjMTIzWA=="), base64_data);
}


TEST(base64, test_hex_to_base64) {
  uint8_t *base64_data = hex_to_base64(
        "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
  );

  uint8_t expected[512] = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
  TEST_ASSERT_EQUAL_MESSAGE(0, strcmp(base64_data, expected), base64_data);
}


TEST_GROUP_RUNNER(base64) {
  RUN_TEST_CASE(base64, test_base64_first_of_four);
  RUN_TEST_CASE(base64, test_base64_second_of_four);
  RUN_TEST_CASE(base64, test_base64_third_of_four);
  RUN_TEST_CASE(base64, test_base64_fourth_of_four);
  RUN_TEST_CASE(base64, test_base64_encode);
  RUN_TEST_CASE(base64, test_base64_decode);
  RUN_TEST_CASE(base64, test_string_to_base64);
  RUN_TEST_CASE(base64, test_hex_to_base64);
}
