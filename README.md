# maketest
simple test library based on a single header and makefile

## maketest.h
Header file to be included in all test code.

NB: It is not required that you include this header in your test code, but it has some useful helper functions.

assert specialisations:
+ assert_are_equal (x, y) : assert two values are equal, using == operator
+ assert_are_equal_t (x, y, t) : assert two values within a given tolerance, using abs() and -
+ assert_are_not_equal (x, y) : assert two values are not equal, using !=
+ assert_is_true (x) : assert x is not equal to 0, using !=
+ assert_is_false (x) : assert x is equal to 0, using ==

Timing wrapper functions:
+ TEST(x) : wrap a function x with timing information
+ TEST_GROUP (x) : wrap a function x with timing information as a group
+ TEST_SUITE (x) : wrap a function x with timing information as a suite

## Makefile
The magic makefile which compiles all the files matching TEST_DIR/*/*.cpp
into test programs.

Each .cpp file will be compiled as a separate executable, so must
contain a main function (see below for an example test code file).

Requirements:
+ Must be included from the main project makefile.
+ Main project makefile should define a TEST_DIR variable
+ TEST_DIR indicates where the .cpp files test code.
+ TEST_DIR must contain a trailing directory separator.

Notes:
+ Creates "bin" subdirectory under TEST_DIR.
+ Test executables are output to TEST_DIR/bin.

See Makefile for a list of commands.

## Example test code file

<PROJECT_DIR>/tests/maths_test.cpp
```cpp
#include "../../maketest/maketest.h"

void abs_test ()
{
  auto a = 1.0f;
  auto b = -2.0f;
  assert_are_equal (abs (a-b), 1.0f);
}

void maths_test_group ()
{
  TEST (abs_test);
}

int main (int argc, char** argv)
{
  TEST_GROUP (maths_test_group);
}
```

## Example Minimum test code file
<PROJECT_DIR>/tests/gt_test.cpp
```cpp
int main (int argc, char** argv)
{
  assert (1 > 0);
}
```

## Example project structure
```
.
|--<PROJECT_DIR>
|  |--src
|  |--include
|  |--tests
|  |  |--gt_test.cpp
|  |  |--maths_test.cpp
|  |--Makefile
|--maketest
|  |--Makefile
|  |--maketest.h
|  |--README.md

```

## Example project Makefile
Makefile in <PROJECT_DIR> should define TEST_DIR include test/Makefile
```
CXX = g++
CXXFLAGS = -std=c++14 $(INCLUDE)
INCLUDE = -Iinclude/ -I../maketest/
LDLIBS = -lpng -lX11 -lGL -lGLEW

TEST_DIR = tests/
include ../maketest/Makefile
```

project Makefile can then call test_all, test_clean, as required.

## Build and run tests
```
> cd <PROJECT_DIR>
> make all_tests
```
