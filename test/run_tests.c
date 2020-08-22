#include "unity_fixture.h"

static void run_all_tests(void) {
  RUN_TEST_GROUP(base64);
  RUN_TEST_GROUP(hex);
  RUN_TEST_GROUP(measures);
  RUN_TEST_GROUP(xor);
}

int main(int argc, const char * argv[]) {
  return UnityMain(argc, argv, run_all_tests);
}
