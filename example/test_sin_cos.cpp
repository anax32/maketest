#include "maketest.h"

void sin_0_test ()
{
  assert_are_equal (0.0, sin (0.0));
}

void sin_pi_test ()
{
  assert_are_equal_t (1.0, sin (3.14159/2.0), 0.01);
}

void cos_0_test ()
{
  assert_are_equal (1.0, cos (0.0));
}

void cos_pi_test ()
{
  assert_are_equal_t (-1.0, cos (3.14159), 0.01);
}

void sin_tests ()
{
  TEST(sin_0_test);
  TEST(sin_pi_test);
}

void cos_tests ()
{
  TEST(cos_0_test);
  TEST(cos_pi_test);
}

int main (int argc, char** argv)
{
  TEST_GROUP(sin_tests);
  TEST_GROUP(cos_tests);
}
