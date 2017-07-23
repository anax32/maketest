#include "maketestcc.h"

TEST_SUITE sin_cos_test_suite
{
  TEST_SET ("sin_tests",
  {
    TEST ("sin_0_test", []() {assert_are_equal (0.0, std::sin (0.0));}),
    TEST ("sin_pi_test",[]() {assert_are_equal (1.0, std::sin (3.14159/2.0), 0.01);}),
  }),
  TEST_SET ("cos_tests",
  {
    TEST ("cos_0_test", []() {assert_are_equal (1.0, std::cos (0.0));}),
    TEST ("cos_pi_test",[]() {assert_are_equal (-1.0, std::cos (3.14159), 0.01);})
  })
};

RUN_SUITE (sin_cos_test_suite);
