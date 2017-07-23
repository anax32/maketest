#include "maketest.h"

void abs_test ()
{
  assert_are_equal (1, abs (1));
  assert_are_equal (1, abs (-1));
}

void abs_tests ()
{
  TEST(abs_test);
}

int main (int argc, char** argv)
{
  TEST_GROUP(abs_tests);
}
