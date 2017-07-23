#include "maketestcc.h"

TEST_SUITE _
{
  TEST_SET ("abs_tests",
  {
    TEST ("abs 1", []() {assert_are_equal (1, abs (1));}),
    TEST ("abs 2", []() {assert_are_equal (1, abs (-1));})
  })
};

RUN_SUITE (_);
