# maketest
simple test library based on a makefile.

Two separate header files are included to help organise tests. It is not required that you include either header in your test code, but it has some useful helper functions.

## maketest.h
Header file with utility functions.
assert_* functions are implemented with the preprocessor.
TEST* functions are implemented with the preprocessor.
timing information is implemented by functions which use std::function.
In future, this dependency will be removed so this header can be used in plain c situations.

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

## maketestcc.h
Header file with utility functions for formatting tests.
Requires c++ initialiser lists.
assert_* functions are implemented as functions.
TEST_* objects are stl containers.
This header allows neater formatting and labelling of test code.
In future, timing information will be added.

assert specialisations:
+ assert_are_equal (x, y) : assert two values are equal, using == operator
+ assert_are_equal (x, y, t) : assert two values are within a given tolerance, using abs() and -

+ TEST (string_name, lambda (void)) : test function with name and code.
+ TEST_SET (string_name, list of TESTs) : test set
+ TEST_SUITE (string_name, list of TEST_SETs): test suite.
+ RUN_TEST (string_name) : name of the test suite to execute.


## Makefile
The magic makefile which compiles all the files matching <TEST_DIR> / \<any> / \<filename>.cpp into test programs.

Each .cpp file will be compiled as a separate executable, so must contain a main function (see below for an example test code file).

Requirements:
+ Must be included from the main project makefile.
+ Main project makefile should define a TEST_DIR variable
+ TEST_DIR indicates where the .cpp files test code.
+ TEST_DIR must contain a trailing directory separator.

Notes:
+ Creates "bin" subdirectory under <TEST_DIR>.
+ Test executables are output to <TEST_DIR>/bin.
+ There is a bug when tests are in the same dir as the makefile:
  + Using an empty <TEST_DIR> means .cpp files are not discovered,
  + Using "." for <TEST_DIR> means executables are written to .bin rather than <TEST_DIR>/bin.
  + Fixing this requires some make voodoo I'm not aware of yet.

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

## Example test code file with neat formatting
<PROJECT_DIR>/tests/mats_test.cpp
```cpp
#include "../../maketest/maketestcc.h"

TEST_SUITE _
{
  TEST_SET ("maths_test_group",
  {
    TEST ("abs test",
    [](){
      auto a = 1.0f;
      auto b = -2.0f;
      assert_are_equal (abs (a-b), 1.0f);
    }
  }
}

RUN_SUITE (_);
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
