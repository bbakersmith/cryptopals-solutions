#include <string.h>

#include "unity.h"
#include "unity_fixture.h"

#include "base64.h"
#include "set1.h"
#include "xor.h"


TEST_GROUP(set1);


TEST_SETUP(set1) {};
TEST_TEAR_DOWN(set1) {};


// 1.2


TEST(set1, test_hex_to_fixed_xor) {
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


// 1.3


TEST(set1, test_char_freq) {
  TEST_ASSERT_EQUAL(50000, char_freq("ABbCcC", 'c'));
  TEST_ASSERT_EQUAL(20000, char_freq("ABbCcCDDDD", 'b'));
  TEST_ASSERT_EQUAL(33333, char_freq("ABC", 'a'));
  TEST_ASSERT_EQUAL(0, char_freq("ABC", 'd'));

  // ignore whitespace
  TEST_ASSERT_EQUAL(50000, char_freq("A Bb CcC", 'c'));
  TEST_ASSERT_EQUAL(20000, char_freq("    ABbCcCDDDD    ", 'b'));
  TEST_ASSERT_EQUAL(33333, char_freq("A BC", 'a'));
  TEST_ASSERT_EQUAL(0, char_freq("A B C", 'd'));
}


TEST(set1, test_magnitude_difference) {
  TEST_ASSERT_EQUAL(100, magnitude_difference(500, 50000));
  TEST_ASSERT_EQUAL(100, magnitude_difference(50000, 500));
  TEST_ASSERT_EQUAL(1, magnitude_difference(500, 500));
  TEST_ASSERT_EQUAL(1, magnitude_difference(50000, 50000));
  TEST_ASSERT_EQUAL(50, magnitude_difference(0, 50));
}


// 1.6


TEST(set1, test_hamming_distance) {
  char a[256] = "this is a test";
  char b[256] = "wokka wokka!!!";
  TEST_ASSERT_EQUAL(37, hamming_distance(a, b, strlen(a)));
}


TEST_GROUP_RUNNER(set1) {
  RUN_TEST_CASE(set1, test_hex_to_fixed_xor);
  RUN_TEST_CASE(set1, test_char_freq);
  RUN_TEST_CASE(set1, test_magnitude_difference);
  RUN_TEST_CASE(set1, test_hamming_distance);
}
