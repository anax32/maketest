#include <iostream>
#include <map>
#include <list>
#include <functional>
#include <cmath>

#ifndef assert
#define assert(expr)  ((expr) ? (void)0 : throw std::exception ())
#endif

template<typename T>
void assert_are_equal (T x, T y)
{
  if (x != y)
    throw std::exception ();
}

template<typename T>
void assert_are_equal (T x, T y, double t)
{
  if (abs (x-y) > t)
    throw std::exception ();
}

typedef std::pair<std::string, std::function<void ()> > TEST;
typedef std::pair<std::string, std::map<std::string, std::function<void ()> > > TEST_SET;
typedef std::map<std::string, std::map<std::string, std::function<void ()> > > TEST_SUITE;
typedef std::list<std::string> DISABLED_TESTS;

void run_tests (TEST_SUITE suite)
{
  int suite_total = 0;
  int suite_failed = 0;

  for (auto& tests : suite)
  {
    int total = tests.second.size ();
    suite_total += total;

    std::cout << tests.first;
    std::cout << " [" << total << "]";
    std::cout << std::endl;

    for (auto& r : tests.second)
    {
      std::cout << "  " << r.first;
      std::cout << "\t";

      // run the test
      try
      {
        r.second ();
      }
      catch (...)
      {
        std::cout << "failed";
        std::cout << std::endl;
        suite_failed++;
        continue;
      }
      // no exception
      {
        std::cout << "passed";
        std::cout << std::endl;
      }
    }
  }

  std::cout << ((float)(suite_total-suite_failed)/suite_total)*100.0f << "%";
  std::cout << " [" << suite_total-suite_failed << "/" << suite_total << "]";
  std::cout << std::endl;

//  return (suite_total - suite_failed);
}

#define RUN_SUITE(x)	int main (int argc, char **argv){run_tests (x); return 0;}
