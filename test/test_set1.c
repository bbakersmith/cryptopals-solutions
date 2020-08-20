#include <string.h>

#include "unity.h"
#include "unity_fixture.h"

#include "base64.h"
#include "set1.h"


TEST_GROUP(set1);


TEST_SETUP(set1) {};
TEST_TEAR_DOWN(set1) {};


// 1.2


TEST(set1, test_array_to_hex) {
  uint8_t data[3] = {255, 0, 28};
  Array input = {
    .length = 3,
    .data = data
  };
  uint8_t *result = array_to_hex(input);
  TEST_ASSERT_EQUAL_MESSAGE(0, strcmp(result, "ff001c"), result);
}


TEST(set1, test_hex_to_fixed_xor) {
  uint8_t *xored_data = hex_to_fixed_xor(
    "1c0111001f010100061a024b53535009181c",
    "686974207468652062756c6c277320657965"
  );

  TEST_ASSERT_EQUAL_MESSAGE(
    0,
    strcmp(xored_data, "746865206b696420646f6e277420706c6179"),
    xored_data
  );
}


// 1.3


TEST(set1, test_char_freq) {
  TEST_ASSERT_EQUAL(50000, char_freq("ABbCcC", 'c'));
  TEST_ASSERT_EQUAL(20000, char_freq("ABbCcCDDDD", 'b'));
  TEST_ASSERT_EQUAL(33333, char_freq("ABC", 'a'));
  TEST_ASSERT_EQUAL(0, char_freq("ABC", 'd'));

  // TODO ignore whitespace
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


TEST(set1, test_single_char_string) {
  TEST_ASSERT_EQUAL(0, strcmp(single_char_string('c', 7), "ccccccc"));
  TEST_ASSERT_EQUAL(0, strcmp(single_char_string('z', 3), "zzz"));
}


TEST(set1, test_decode_hex_string) {
  uint8_t *result = decode_hex_string("616263");
  TEST_ASSERT_EQUAL_MESSAGE(0, strcmp(result, "abc"), result);
}


// 1.5


TEST(set1, test_encode_hex_string) {
  uint8_t *result = encode_hex_string("abc");
  TEST_ASSERT_EQUAL_MESSAGE(0, strcmp(result, "616263"), result);
}


TEST(set1, test_encode_repeating_key_xor) {
  uint8_t input[256] = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";

  encode_repeating_key_xor(input, "ICE");

  uint8_t *result = encode_hex_string(input);

  uint8_t expected[512] = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";

  TEST_ASSERT_EQUAL_MESSAGE(
    0,
    strcmp(result, expected),
    result
  );
}


// 1.6


TEST(set1, test_hamming_distance) {
  uint8_t a[256] = "this is a test";
  uint8_t b[256] = "wokka wokka!!!";
  TEST_ASSERT_EQUAL(37, hamming_distance(a, b, strlen(a)));
}


// TODO implement
TEST(set1, test_decode_repeating_key_xor) {
  uint8_t hex_input[512] = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";

  uint8_t *input = decode_hex_string(hex_input);

  decode_repeating_key_xor(input, "ICE");

  uint8_t expected[256] = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";

  TEST_ASSERT_EQUAL_MESSAGE(
    0,
    strcmp(input, expected),
    input
  );
}


TEST_GROUP_RUNNER(set1) {
  RUN_TEST_CASE(set1, test_array_to_hex);
  RUN_TEST_CASE(set1, test_hex_to_fixed_xor);
  RUN_TEST_CASE(set1, test_char_freq);
  RUN_TEST_CASE(set1, test_magnitude_difference);
  /* RUN_TEST_CASE(set1, test_single_char_string); */
  RUN_TEST_CASE(set1, test_decode_hex_string);
  RUN_TEST_CASE(set1, test_encode_repeating_key_xor);
  RUN_TEST_CASE(set1, test_encode_hex_string);
  RUN_TEST_CASE(set1, test_hamming_distance);
  RUN_TEST_CASE(set1, test_decode_repeating_key_xor);
}
