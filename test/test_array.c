#include <string.h>

#include "unity.h"
#include "unity_fixture.h"

#include "array.h"


TEST_GROUP(array);


TEST_SETUP(array) {};
TEST_TEAR_DOWN(array) {};


TEST(array, test_array_remove_value) {
  char result[256];
  Array input_arr = array_from_string("foo bar baz\nzig zag");

  array_remove_value(&input_arr, '\n');
  array_to_string(&input_arr, result);

  TEST_ASSERT_EQUAL_MESSAGE(
    0,
    strcmp("foo bar bazzig zag", result),
    result
  );

  array_remove_value(&input_arr, ' ');
  array_to_string(&input_arr, result);

  TEST_ASSERT_EQUAL_MESSAGE(
    0,
    strcmp("foobarbazzigzag", result),
    result
  );

  array_free(&input_arr);
}


TEST_GROUP_RUNNER(array) {
  RUN_TEST_CASE(array, test_array_remove_value);
}
