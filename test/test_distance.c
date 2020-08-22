#include <string.h>

#include "unity.h"
#include "unity_fixture.h"

#include "distance.h"


TEST_GROUP(distance);


TEST_SETUP(distance) {};
TEST_TEAR_DOWN(distance) {};


TEST(distance, test_char_freq) {
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


TEST(distance, test_magnitude_difference) {
  TEST_ASSERT_EQUAL(100, magnitude_difference(500, 50000));
  TEST_ASSERT_EQUAL(100, magnitude_difference(50000, 500));
  TEST_ASSERT_EQUAL(1, magnitude_difference(500, 500));
  TEST_ASSERT_EQUAL(1, magnitude_difference(50000, 50000));
  TEST_ASSERT_EQUAL(50, magnitude_difference(0, 50));
}


TEST(distance, test_hamming_distance) {
  char a[256] = "this is a test";
  char b[256] = "wokka wokka!!!";
  TEST_ASSERT_EQUAL(37, hamming_distance(a, b, strlen(a)));
}


TEST_GROUP_RUNNER(distance) {
  RUN_TEST_CASE(distance, test_char_freq);
  RUN_TEST_CASE(distance, test_magnitude_difference);
  RUN_TEST_CASE(distance, test_hamming_distance);
}
